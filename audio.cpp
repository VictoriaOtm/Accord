#include "audio.h"
#include <QtMultimedia>

Audio::Audio(QString path)
{
    this->path = path;
    LoadMetaData();
}



QVector<Audio> Audio::fromAudioPaths(const QStringList &paths){
    QVector<Audio> result;
    for(auto iter = paths.begin() ; iter != paths.end() ; ++i){
        Audio audio(*i);
        result.append(audio);
    }
    return result;
}

const QString& Audio::GetPath() const{
    return path;
}

void Audio::LoadMetaData(){
    QAudioDecoder d;
    d.setSourceFilename(path);
    QStringList metaDataKeys = d.availableMetaData();

    title = (metaDataKeys.contains("Title") ? d.metaData("Title").toString() : "Unknown title" );
    authors = (metaDataKeys.contains("Author") ? d.metaData("Author").toStringList() : QStringList("Unknown author") );
    title = (metaDataKeys.contains("AlbumTitle") ? d.metaData("AlbumTitle").toString() : "Unknown album" );
}
