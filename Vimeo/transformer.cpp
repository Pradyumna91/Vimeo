#include "transformer.h"
#include <Timeline.h>
#include <FFmpegReader.h>
#include <QSettings>

Transformer::Transformer(QObject *parent) : QObject(parent)
{

}

void Transformer::addOverlay(QString video, QString imageFilePath)
{
    if(video == nullptr)
        return;

    // Create some clips
    ImageReader* imr = new ImageReader(imageFilePath.toStdString());
    FFmpegReader* ivr = new FFmpegReader(video.toStdString());
    Clip imageClip;
    imageClip.Reader(imr);
    Clip videoClip;
    videoClip.Reader(ivr);
    imr->Open();
    ivr->Open();

    Timeline t(ivr->info.width, // width
               ivr->info.height, // height
               Fraction(25,1), // framerate
               ivr->info.sample_rate, // sample rate
               2 // channels
               );

    // CLIP 1 (logo) - Set some clip properties (with Keyframes)
    videoClip.Position(0.0); // Set the position or location (in seconds) on the timeline
    videoClip.Layer(0); // Set the layer of the timeline (higher layers cover up images of lower layers)
    videoClip.Start(0.0); // Set the starting position of the video (trim the left side of the video)
    videoClip.End(ivr->info.duration); // Set the ending position of the video (trim the right side of the video)

    int startingFrame = ivr->info.video_length/3;

    // CLIP 2 (background video) - Set some clip properties (with Keyframes)
    imageClip.alpha.AddPoint(1, 1.0);
    imageClip.alpha.AddPoint(startingFrame, 0.0);
    imageClip.alpha.AddPoint((startingFrame * 2), 1.0);
    imageClip.gravity = GravityType::GRAVITY_BOTTOM;
    imageClip.Start(0.0); // Set the starting position of the video (trim the left side of the video)
    imageClip.Layer(1); // Set the layer of the timeline (higher layers cover up images of lower layers)

    // Add clips to timeline
    t.AddClip(&videoClip);
    t.AddClip(&imageClip);
    // Open the timeline reader
    t.Open();

    QSettings settings;
    QString outputFilename = settings.value("VideoFilesDumpPath").toString() + "editedvid.webm";
    FFmpegWriter w(outputFilename.toStdString());
    w.SetAudioOptions(true, "libvorbis", ivr->info.sample_rate, ivr->info.channels, ivr->info.channel_layout, ivr->info.audio_bit_rate);
    w.SetVideoOptions(true, "libvpx", ivr->info.fps, ivr->info.width, ivr->info.height, ivr->info.pixel_ratio, ivr->info.interlaced_frame, ivr->info.top_field_first, ivr->info.video_bit_rate);
    w.Open();
    w.WriteFrame(&t, 1, ivr->info.video_length);
    w.Close();
    t.Close();

    emit editingDone(outputFilename);
}
