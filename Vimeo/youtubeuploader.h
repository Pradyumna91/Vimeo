#ifndef YOUTUBEUPLOADER_H
#define YOUTUBEUPLOADER_H
#include "videouploader.h"
#include "webviewdialog.h"
#include "video.h"

#include <QString>
#include <QUrl>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

class YoutubeUploader : public VideoUploader
{
    Q_OBJECT
private:
    static const QString clientID;
    static const QString clientSecret;
    static const QString authRequestURLBase;
    static const QString redirectUri;
    static const QString scope;
    static const QString uploadUrl;
    static const QString tokensFilePath;
    static const qint64 cipherSeed;

    Video* videoToUpload;
    QString accessToken, refreshToken;
    WebViewDialog* view;

    QUrl getAuthRequestURL();
    void showWebPage();
    void writeTokensToFile(QString, QString);
    QJsonDocument *createSnippetJson(Video *);
    void startUpload(Video*, QString);
    void readTokensFromFile();
    void refreshAccessTokens();

public:
    YoutubeUploader();
    void upload();
    ~YoutubeUploader();
    void beginUploadProcess(Video* vid);

public slots:
    void requestForAccessTokens(QString);
    void populateAccessTokens(QNetworkReply *);
    void handleCreateUploadSessionResponse(QNetworkReply*);
    void cleanupAfterUpload(QNetworkReply*);
    void initialiseUploadSession();

signals:
    void tokensReceived();
};

#endif // YOUTUBEUPLOADER_H
