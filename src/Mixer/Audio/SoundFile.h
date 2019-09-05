#pragma once

#include <SFML/Audio.hpp>

class SoundFile {
public:
  virtual int getSampleRate() const = 0;

  const std::vector<double> &getLeftSamples() const {
      return m_leftBuffer;
  }

  const std::vector<double> &getRightSamples() const {
      return m_rightBuffer;
  }
  std::vector<double> m_leftBuffer;
  std::vector<double> m_rightBuffer;
};

class TestSoundFile : public SoundFile {
public:
    explicit TestSoundFile(const tPath& path) {


        auto loopRange = [](auto* begin, const auto count, auto cb) {
            for(auto i = 0; i < count; i++) {
                cb(begin[i]);
            }
        };

        if(!m_buffer.loadFromFile(path.string()))
            throw std::runtime_error("could not load file: " + path.string());


        auto currentMax = 1.0;
        loopRange(m_buffer.getSamples(), m_buffer.getSampleCount(), [&currentMax](const sf::Int16& in) {
            currentMax = std::max<double>(in, currentMax);
        });

        if(m_buffer.getChannelCount() == 1) {
            for(auto i = 0; i < m_buffer.getSampleCount(); i++) {
                auto sample = m_buffer.getSamples()[i] / currentMax;
                m_rightBuffer.emplace_back(sample);
                m_leftBuffer.emplace_back(sample);
            }
        } else if(m_buffer.getChannelCount() == 2) {
            for(auto i = 0; i + 1 < m_buffer.getSampleCount(); i+=2) {
                auto left = m_buffer.getSamples()[i] / currentMax;
                auto right = m_buffer.getSamples()[i+1] / currentMax;
                m_leftBuffer.emplace_back(left);
                m_rightBuffer.emplace_back(right);
            }
        } else {
            throw std::runtime_error("unsupported channel count! is: " + std::to_string(m_buffer.getChannelCount()));
        }
    }
    int getSampleRate() const override {
        return m_buffer.getSampleRate();
    }
protected:
    sf::SoundBuffer m_buffer;
};

/*
// Function prototypes
int getFileSize(FILE* inFile);

int main(int argc, char* argv[])
{
    wav_hdr wavHeader;
    int headerSize = sizeof(wav_hdr), filelength = 0;

    const char* filePath;
    string input;
    if (argc <= 1)
    {
        cout << "Input wave file name: ";
        cin >> input;
        cin.get();
        filePath = input.c_str();
    }
    else
    {
        filePath = argv[1];
        cout << "Input wave file name: " << filePath << endl;
    }

    FILE* wavFile = fopen(filePath, "r");
    if (wavFile == nullptr)
    {
        fprintf(stderr, "Unable to open wave file: %s\n", filePath);
        return 1;
    }

    //Read the header
    size_t bytesRead = fread(&wavHeader, 1, headerSize, wavFile);
    cout << "Header Read " << bytesRead << " bytes." << endl;
    if (bytesRead > 0)
    {
        //Read the data
        uint16_t bytesPerSample = wavHeader.bitsPerSample / 8;      //Number of
bytes per sample uint64_t numSamples = wavHeader.ChunkSize / bytesPerSample;
//How many samples are in the wav file? static const uint16_t BUFFER_SIZE =
4096; int8_t* buffer = new int8_t[BUFFER_SIZE]; while ((bytesRead =
fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), wavFile)) > 0)
        {
cout << "Read " << bytesRead << " bytes." << endl;
}
delete[] buffer;
buffer = nullptr;
filelength = getFileSize(wavFile);

cout << "File is                    :" << filelength << " bytes." << endl;
cout << "RIFF header                :" << wavHeader.RIFF[0] << wavHeader.RIFF[1]
     << wavHeader.RIFF[2] << wavHeader.RIFF[3] << endl;
cout << "WAVE header                :" << wavHeader.WAVE[0] << wavHeader.WAVE[1]
     << wavHeader.WAVE[2] << wavHeader.WAVE[3] << endl;
cout << "FMT                        :" << wavHeader.fmt[0] << wavHeader.fmt[1]
     << wavHeader.fmt[2] << wavHeader.fmt[3] << endl;
cout << "Data size                  :" << wavHeader.ChunkSize << endl;

// Display the sampling Rate from the header
cout << "Sampling Rate              :" << wavHeader.SamplesPerSec << endl;
cout << "Number of bits used        :" << wavHeader.bitsPerSample << endl;
cout << "Number of channels         :" << wavHeader.NumOfChan << endl;
cout << "Number of bytes per second :" << wavHeader.bytesPerSec << endl;
cout << "Data length                :" << wavHeader.Subchunk2Size << endl;
cout << "Audio Format               :" << wavHeader.AudioFormat << endl;
// Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

cout << "Block align                :" << wavHeader.blockAlign << endl;
cout << "Data string                :" << wavHeader.Subchunk2ID[0]
     << wavHeader.Subchunk2ID[1] << wavHeader.Subchunk2ID[2]
     << wavHeader.Subchunk2ID[3] << endl;
}
fclose(wavFile);
return 0;
}

// find the file size
int getFileSize(FILE *inFile) {
  int fileSize = 0;
  fseek(inFile, 0, SEEK_END);

  fileSize = ftell(inFile);

  fseek(inFile, 0, SEEK_SET);
  return fileSize;
}
*/