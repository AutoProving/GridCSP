// Copyright (c) 2019-2020 Mateus de Oliveira Oliveira and Contributors. 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

/**
 * @file ListColoring/LegacyWriter.h
 * Provides reader to a legacy-style format.
 *
 * The format is self-explanatory. Find an example in "listColoringExample.tex"
 * file in the source repository.
 */

#include <ListColoring/ListColoring.h>

#include <stdexcept>
#include <string>
#include <iostream>

namespace ListColoring {
namespace Legacy {

/**
 * @brief A legacy reader format error.
 *
 * Could be either a tokenizer, parser or logic error.
 */
class ReaderError : public std::runtime_error {
public:
    ReaderError(const std::string& message);
};

/**
 * @brief Read an instance description in legacy format from stream.
 * @throws ReaderError In case of format error.
 */
ProblemInstance read(std::istream& is);

/**
 * @brief Read an instance description in legacy format from stream.
 * @throws ReaderError In case of format error.
 */
ProblemInstance read(const std::string& description);

}
}
