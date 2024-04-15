import pyaudio
import numpy as np
import wave
import sounddevice as sd
import soundfile as sf

FORMAT = pyaudio.paInt16
CHANNELS = 1
SAMPLE_RATE = 44100
CHUNK = 1024
RECORD_SECONDS = 5
WAVE_OUTPUT_FILENAME = "output.wav"
QUANTIZATION_LEVELS = 256

def quantize(signal, levels):
    signal_min = np.min(signal)
    signal_max = np.max(signal)
    q = (signal_max - signal_min) / levels
    return np.round((signal - signal_min) / q) * q + signal_min

print("Przetwarzanie analogowo-cyfrowe A/C")
print("1.Nagrywanie")
print("2.Odtwarzanie")
choice = input("Wybór: ")
if choice == "1":
    print("siema")
    audio = pyaudio.PyAudio()
    stream = audio.open(format=FORMAT, channels=CHANNELS,
                    rate=SAMPLE_RATE, input=True,
                    frames_per_buffer=CHUNK)
    print("Recording...")
    frames = []
    for i in range(0, int(SAMPLE_RATE / CHUNK * RECORD_SECONDS)):
        data = stream.read(CHUNK)
        frames.append(data)
    print("Finished recording.")
    stream.stop_stream()
    stream.close()
    audio.terminate()
    signal = np.frombuffer(b''.join(frames), dtype=np.int16)
    quantized_signal = quantize(signal, QUANTIZATION_LEVELS)
    quantized_signal = np.int16(quantized_signal)
    wf = wave.open(WAVE_OUTPUT_FILENAME, 'wb')
    wf.setnchannels(CHANNELS)
    wf.setsampwidth(audio.get_sample_size(FORMAT))
    wf.setframerate(SAMPLE_RATE)
    wf.writeframes(quantized_signal.tobytes())
    wf.close()
    print("File saved as " + WAVE_OUTPUT_FILENAME)
elif choice == "2":
    data, sampling = sf.read("output.wav")
    data = data / np.max(np.abs(data))
    sd.play(data, sampling)
    sd.wait()
