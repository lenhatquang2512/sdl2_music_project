#include <iostream>
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>

int main() {
    // Replace "path/to/your/audio/file.mp3" with the actual path to your MP3 file
    TagLib::FileRef fileRef("../music_files/gruppa-krovi.mp3");

    if (fileRef.isNull()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    // Get the Tag (metadata) of the file
    TagLib::Tag* tag = fileRef.tag();

    // Display some metadata information
    std::cout << "Title: " << tag->title().toCString(true) << std::endl;
    std::cout << "Artist: " << tag->artist().toCString(true) << std::endl;
    std::cout << "Album: " << tag->album().toCString(true) << std::endl;
    std::cout << "Year: " << tag->year() << std::endl;
    std::cout << "Track: " << tag->track() << std::endl;

    TagLib::AudioProperties *properties = fileRef.audioProperties();
    std::cout << "Bitrate: " << properties->bitrate() << std::endl;
    std::cout << "Length: " << properties->lengthInSeconds()/60.0f << " min" << std::endl;
    std::cout << "Channels: " << properties->channels() << std::endl;

    return 0;
}

