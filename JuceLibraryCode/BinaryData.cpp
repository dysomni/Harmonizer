/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== COPYING.txt ==================
static const unsigned char temp_binary_data_0[] =
"Copyright (c) 2017 HiFi-LoFi\n"
"\n"
"Permission is hereby granted, free of charge, to any person obtaining a copy\n"
"of this software and associated documentation files (the \"Software\"), to deal\n"
"in the Software without restriction, including without limitation the rights\n"
"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
"copies of the Software, and to permit persons to whom the Software is furnished\n"
"to do so, subject to the following conditions:\n"
"\n"
"The above copyright notice and this permission notice shall be included in\n"
"all copies or substantial portions of the Software.\n"
"\n"
"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS\n"
"FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR\n"
"COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER\n"
"IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION\n"
"WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n";

const char* COPYING_txt = (const char*) temp_binary_data_0;

//================== README.md ==================
static const unsigned char temp_binary_data_1[] =
"AudioFFT\r\n"
"========\r\n"
"\r\n"
"AudioFFT provides real-to-complex/complex-to-real FFT routines.\r\n"
"\r\n"
"## Features ##\r\n"
"\r\n"
"- Real-complex FFT and complex-real inverse FFT for power-of-2-sized real data.\r\n"
"\r\n"
"- Uniform interface to different FFT implementations (currently Ooura, FFTW3, Apple Accelerate and Intel IPP).\r\n"
"\r\n"
"- Complex data is handled in \"split-complex\" format, i.e. there are separate\r\n"
"  arrays for the real and imaginary parts which can be useful for SIMD optimizations\r\n"
"  (split-complex arrays have to be of length (size/2+1) representing bins from DC\r\n"
"  to Nyquist frequency).\r\n"
"\r\n"
"- Output is \"ready to use\" (all scaling etc. is already handled internally).\r\n"
"\r\n"
"- No allocations/deallocations after the initialization which makes it usable\r\n"
"  for real-time audio applications (that's what I wrote it for and using it).\r\n"
"\r\n"
"\r\n"
"## How to use it in your project ##\r\n"
"\r\n"
"- Add the .h and .cpp file to your project - that's all.\r\n"
"\r\n"
"\r\n"
"- To get extra speed, you can link FFTW3 to your project and define\r\n"
"  AUDIOFFT_FFTW3 (however, please check whether your project suits the\r\n"
"  according license).\r\n"
"\r\n"
"- To get the best speed on Apple platforms, you can link the Apple\r\n"
"  Accelerate framework to your project and define AUDIOFFT_APPLE_ACCELERATE.\r\n"
"\r\n"
"- On any supported platform you can use Intel IPP's FFT's by linking to IPP and defining AUDIOFFT_INTEL_IPP.\r\n"
"\r\n"
"## Remarks ##\r\n"
"\r\n"
"- AudioFFT is not intended to be the fastest FFT, but to be a fast-enough\r\n"
"  FFT suitable for most audio applications.\r\n"
"  \r\n"
"- AudioFFT uses the quite liberal MIT license.\r\n"
"\r\n"
"\r\n"
"## Example usage ##\r\n"
"\r\n"
"    #include \"AudioFFT.h\"\r\n"
"    \r\n"
"    void Example()\r\n"
"    {\r\n"
"      const size_t fftSize = 1024; // Needs to be power of 2!\r\n"
"      \r\n"
"      std::vector<float> input(fftSize, 0.0f);\r\n"
"      std::vector<float> re(fftaudio::AudioFFT::ComplexSize(fftSize)); \r\n"
"      std::vector<float> im(fftaudio::AudioFFT::ComplexSize(fftSize)); \r\n"
"      std::vector<float> output(fftSize);\r\n"
"      \r\n"
"      audiofft::AudioFFT fft;\r\n"
"      fft.init(1024);\r\n"
"      fft.fft(input.data(), re.data(), im.data());\r\n"
"      fft.ifft(output.data(), re.data(), im.data());\r\n"
"    }\r\n"
"\r\n"
"\r\n"
"## Benchmarks ##\r\n"
"\r\n"
"The following tables show time measurements for forward/backward \"FFTing\" 512MB\r\n"
"of real data using the FFT input size as listed in the tables.\r\n"
"\r\n"
"AudioFFT was run using internally Ooura, FFTW3 and vDSP (Apple Accelerate).\r\n"
"\r\n"
"For comparison and reference, the same setup also was used with the great\r\n"
"KissFFT, which is a quite popular FFT implementation, and which is also able\r\n"
"to handle non-power-of-2 sizes. :-)\r\n"
"\r\n"
"\r\n"
"#### CPU: Intel Core i5 (2,4 GHz) ####\r\n"
"- Mac OS X Lion 10.7.5\r\n"
"- Compiler: Apple LLVM 3.0 (/Os (fastest, smallest), SSE enabled) \r\n"
"\r\n"
"| Size |  Ooura  |  FFTW3  |  Apple  | KissFFT |\r\n"
"| ----:| -------:| -------:| -------:| -------:|\r\n"
"|   64 |  8.805s |  6.914s |  3.420s | 12.496s |\r\n"
"|  128 | 10.047s |  6.473s |  2.992s | 11.457s |\r\n"
"|  512 | 11.895s |  6.473s |  3.025s | 13.737s |\r\n"
"| 1024 | 12.956s |  6.932s |  3.139s | 17.050s |\r\n"
"| 4096 | 14.840s |  7.517s |  3.661s | 19.379s |\r\n"
"\r\n"
"\r\n"
"#### CPU: Intel Xeon (2.93 GHz) ####\r\n"
"- Windows 7\r\n"
"- Compiler: VC10 (/O2 /arch:SSE2 /fp:precise)\r\n"
"\r\n"
"| Size |  Ooura  |  FFTW3  | KissFFT |\r\n"
"| ----:| -------:| -------:| -------:|\r\n"
"|   64 |  7.267s |  4.625s | 20.819s |\r\n"
"|  128 |  7.583s |  5.494s | 20.822s |\r\n"
"|  512 |  8.608s |  5.346s | 24.812s |\r\n"
"| 1024 |  9.546s |  5.604s | 28.936s |\r\n"
"| 4096 | 11.026s |  6.265s | 33.160s |\r\n";

const char* README_md = (const char*) temp_binary_data_1;

//================== README.md ==================
static const unsigned char temp_binary_data_2[] =
"# audio_fft\n"
"JUCE module wrapper for the AudioFFT library\n";

const char* README_md2 = (const char*) temp_binary_data_2;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x6c06575e:  numBytes = 1053; return COPYING_txt;
        case 0x64791dc8:  numBytes = 3419; return README_md;
        case 0x2aaa9b6a:  numBytes = 57; return README_md2;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "COPYING_txt",
    "README_md",
    "README_md2"
};

const char* originalFilenames[] =
{
    "COPYING.txt",
    "README.md",
    "README.md"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
