#include "youtubeuploader.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QWebView>
#include <QUrlQuery>
#include <QUrl>
#include <QJsonArray>


const QString YoutubeUploader::clientID = "428706088869-qct812sg761c6vkulvhdholas8c9iuoo.apps.googleusercontent.com";
const QString YoutubeUploader::clientSecret = "_3wX4tCJvgydwI_i8ec3XEst";
const QString YoutubeUploader::authRequestURLBase = "https://accounts.google.com/o/oauth2";
const QString YoutubeUploader::redirectUri = "urn:ietf:wg:oauth:2.0:oob";
const QString YoutubeUploader::scope = "https://www.googleapis.com/auth/youtube.upload";
const QString YoutubeUploader::uploadUrl = "https://www.googleapis.com/upload/youtube/v3/videos";

YoutubeUploader::YoutubeUploader() : VideoUploader()
{
    view = new WebViewDialog();
    accessToken = "";
    refreshToken = "";
}

YoutubeUploader::~YoutubeUploader()
{
    delete view;
}

void YoutubeUploader::beginUploadProcess(Video* vid)
{
    if(vid == NULL)
        return;

    videoToUpload = vid;
    upload();
}

void YoutubeUploader::upload()
{
    connect(this, SIGNAL(tokensReceived()), this, SLOT(initialiseUploadSession()));
    if (accessToken.isEmpty())
    {
        showWebPage();
    }
}

void YoutubeUploader::initialiseUploadSession()
{
    QFile videoFile(videoToUpload->getFilepath());

    if(videoFile.open(QIODevice::ReadOnly))
    {
        QByteArray contents = createSnippetJson(videoToUpload)->toJson();
        qint64 fileLenth = videoFile.bytesAvailable();
        videoFile.close();

        //Creating the resumable download request object============================
        QUrlQuery params;
        params.addQueryItem("uploadType", "resumable");
        params.addQueryItem("part", "snippet");
        QUrl uplUrl(uploadUrl);
        uplUrl.setQuery(params.query(QUrl::FullyEncoded).toUtf8());
        QNetworkRequest* req = new QNetworkRequest(uplUrl);

        req->setHeader(QNetworkRequest::ContentLengthHeader, contents.length());
        req->setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
        req->setRawHeader(QByteArray("X-Upload-Content-Length"), QByteArray().setNum(fileLenth));
        req->setRawHeader(QByteArray("X-Upload-Content-Type"), QByteArray("video/*"));
        req->setRawHeader(QByteArray("Authorization"), QString("Bearer %1").arg(accessToken).toUtf8());
        //=====================================================================

        connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleCreateUploadSessionResponse(QNetworkReply*)));
        mgr->post(*req, contents);

    }
}

void YoutubeUploader::handleCreateUploadSessionResponse(QNetworkReply *reply)
{
    if(reply != NULL && reply->error() == QNetworkReply::NoError)
    {
        if(reply->hasRawHeader(QByteArray("Location")))
        {
            QString uploadUri = reply->rawHeader(QByteArray("Location"));
            startUpload(videoToUpload, uploadUri);
        }
    }
}

void YoutubeUploader::startUpload(Video * vid, QString uplUri)
{
    QFile* v = new QFile(vid->getFilepath());
    if(v->open(QIODevice::ReadOnly))
    {
        //Creating the upload request object============================
        QNetworkRequest* req = new QNetworkRequest(QUrl(uplUri));

        req->setHeader(QNetworkRequest::ContentLengthHeader, v->bytesAvailable());
        req->setHeader(QNetworkRequest::ContentTypeHeader, "video/*");
        req->setRawHeader(QByteArray("Authorization"), QString("Bearer %1").arg(accessToken).toUtf8());
        //=====================================================================

        connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(cleanupAfterUpload(QNetworkReply*)));
        mgr->post(*req, v->readAll());
    }
}

void YoutubeUploader::cleanupAfterUpload(QNetworkReply *reply)
{
    if(reply != NULL && reply->error() == QNetworkReply::NoError)
    {
        delete videoToUpload;
        emit uploadComplete(UploadManager::YOUTUBE);
    }
}

QUrl YoutubeUploader::getAuthRequestURL()
{
    QString urlAsString = QString("%1/%2?client_id=%3&redirect_uri=%4&scope=%5&response_type=%6").
            arg(authRequestURLBase, "auth", clientID, redirectUri, scope, "code");

    return QUrl(urlAsString);
}

void YoutubeUploader::showWebPage()
{
    QUrl authUrl = getAuthRequestURL();
    view->getWebView()->load(authUrl);
    connect(view->getWebView(), SIGNAL(titleChanged(QString)), this, SLOT(requestForAccessTokens(QString)));

    view->exec();
}

void YoutubeUploader::requestForAccessTokens(QString newTitle)
{
    if(newTitle.startsWith("Success"))
    {
        QString authCode = newTitle.split(" ").last().split("=").last();
        QUrl url(QString("%1/%2").arg(authRequestURLBase, "token"));

        view->close();

        QUrlQuery params;
        params.addQueryItem("code", authCode);
        params.addQueryItem("client_id", clientID);
        params.addQueryItem("client_secret", clientSecret);
        params.addQueryItem("redirect_uri", redirectUri);
        params.addQueryItem("grant_type", "authorization_code");

        QNetworkRequest req(url);

        req.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));

        connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(populateAccessTokens(QNetworkReply*)));
        mgr->post(req, params.query(QUrl::FullyEncoded).toUtf8());
    }
}

void YoutubeUploader::populateAccessTokens(QNetworkReply *reply)
{
    if(reply != NULL && reply->error() == QNetworkReply::NoError)
    {
        QString replyText = reply->readAll();
        QJsonDocument response = QJsonDocument::fromJson(replyText.toUtf8());
        QJsonObject obj = response.object();

        accessToken = obj["access_token"].isString() ? obj["access_token"].toString() : "";
        refreshToken = obj["refresh_token"].isString() ? obj["refresh_token"].toString() : "";

        disconnect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(populateAccessTokens(QNetworkReply*)));
        writeTokensToFile(accessToken, refreshToken);
    }
}

QJsonDocument* YoutubeUploader::createSnippetJson(Video* vid)
{
    QJsonObject snippetObj;
    snippetObj["title"] = vid->getTitle();
    snippetObj["description"] = vid->getDescription();
    snippetObj["categoryId"] = 22;
    QJsonArray allTags;
    for (int i = 0; i < vid->getTags()->count(); i++)
    {
        allTags.append(QJsonValue(vid->getTags()->at(i)));
    }
    snippetObj["tags"] = allTags;

    QJsonDocument* doc = new QJsonDocument(snippetObj);
    return doc;
}

void YoutubeUploader::writeTokensToFile(QString actk, QString rftk)
{
    emit tokensReceived();
}
