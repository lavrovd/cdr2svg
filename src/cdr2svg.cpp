/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libcdr project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Modifications for `cdr2svg`:
 * - Changed the tool to convert CorelDRAW documents directly to SVG.
 * - Removed additional XML and XHTML wrappers to output pure SVG content.
 * - Updated usage and version information to reflect the new functionality.
 * - Simplified output to clean SVG structure.
 *
 * Original file name: cdr2xhtml.cpp
 * Modified file name: cdr2svg.cpp
 * Modifications by: Dmitry Lavrov and contributors
 * Date: 16-01-2025
 *
 * Report bugs to <https://bugs.documentfoundation.org/>.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <libcdr/libcdr.h>
#include <librevenge-generators/librevenge-generators.h>
#include <librevenge-stream/librevenge-stream.h>
#include <librevenge/librevenge.h>
#include <stdio.h>
#include <string.h>

#ifndef VERSION
#define VERSION "UNKNOWN VERSION"
#endif

namespace {

int printUsage()
{
    printf("`cdr2svg' converts CorelDRAW documents to SVG.\n");
    printf("\n");
    printf("Usage: cdr2svg [OPTION] FILE\n");
    printf("\n");
    printf("Options:\n");
    printf("\t--help                show this help message\n");
    printf("\t--version             show version information and exit\n");
    printf("\n");
    printf("Report bugs to <https://bugs.documentfoundation.org/>.\n");
    return -1;
}

int printVersion()
{
    printf("cdr2svg " VERSION "\n");
    return 0;
}

} // anonymous namespace

int main(int argc, char* argv[])
{
    if (argc < 2)
        return printUsage();

    char* file = nullptr;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--version"))
            return printVersion();
        else if (!file && strncmp(argv[i], "--", 2))
            file = argv[i];
        else
            return printUsage();
    }

    if (!file)
        return printUsage();

    librevenge::RVNGFileStream input(file);
    librevenge::RVNGStringVector output;
    librevenge::RVNGSVGDrawingGenerator painter(output, "svg");

    if (!libcdr::CDRDocument::isSupported(&input)) {
        if (!libcdr::CMXDocument::isSupported(&input)) {
            fprintf(stderr, "ERROR: Unsupported file format (unsupported version) or file is encrypted!\n");
            return 1;
        } else if (!libcdr::CMXDocument::parse(&input, &painter)) {
            fprintf(stderr, "ERROR: Parsing of document failed!\n");
            return 1;
        }
    } else if (!libcdr::CDRDocument::parse(&input, &painter)) {
        fprintf(stderr, "ERROR: Parsing of document failed!\n");
        return 1;
    }

    if (output.empty()) {
        std::cerr << "ERROR: No SVG document generated!" << std::endl;
        return 1;
    }

    for (unsigned k = 0; k < output.size(); ++k) {
        if (k > 0)
            std::cout << "\n";

        std::cout << output[k].cstr() << std::endl;
    }

    return 0;
}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
