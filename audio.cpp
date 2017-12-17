#include "audio.h"
#include <QtMultimedia>

Audio::Audio(QString path)
{
    this->path = path;
    ssize_t startIndexNameSong = path.lastIndexOf(QString::fromLocal8Bit("/"));
    ssize_t endIndexNameSong = path.lastIndexOf(QString::fromLocal8Bit("."));
    this->filename = path.mid(startIndexNameSong + 1, endIndexNameSong - startIndexNameSong - 1);
    LoadMetaData();
}

QVector<Audio> Audio::fromAudioPaths(const QStringList &paths){
    QVector<Audio> result;
    for(auto iter = paths.begin() ; iter != paths.end() ; ++iter){
        Audio audio(*iter);
        result.append(audio);
    }
    return result;
}

const QString& Audio::GetPath() const{
    return path;
}

const QString& Audio::GetFilename() const{
    return filename;
}

const QString& Audio::GetTitle() const{
    return title;
}

const QStringList& Audio::GetAuthors() const{
    return authors;
}

const QString& Audio::GetAlbumTitle() const{
    return album;
}

void Audio::LoadMetaData(){
    QAudioDecoder d;
    d.setSourceFilename(path);
    QStringList metaDataKeys = d.availableMetaData();

    title = (metaDataKeys.contains("Title") ? d.metaData("Title").toString() : "Unknown title" );
    authors = (metaDataKeys.contains("Author") ? d.metaData("Author").toStringList() : QStringList("Unknown author") );
    title = (metaDataKeys.contains("AlbumTitle") ? d.metaData("AlbumTitle").toString() : "Unknown album" );
}

bool Audio::operator == (const Audio& other) const{
    return this->GetPath() == other.GetPath();
}
