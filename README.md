# cdr2svg: A Docker Image for CorelDRAW to SVG Conversion

cdr2svg is a Docker-based tool for converting CorelDRAW files (.cdr) into SVG format. It is a modification of the original cdr2xhtml tool, updated to output pure SVG files directly. This project bundles all necessary dependencies within the Docker image, ensuring ease of use and compatibility.

## Features

- **CorelDRAW** to **SVG** Conversion: Easily convert **CorelDRAW** files (.cdr) into **SVG**, preserving vector graphic fidelity.
- Standalone Docker Image: Requires no local installation of dependencies; all necessary tools and libraries are included.
- Self-Contained: Includes libcdr and librevenge libraries to parse and process **CorelDRAW** files.
- Easy to Use: Minimal command-line interaction for quick and reliable conversions.

## Usage

1. Building the Docker Image
    Clone this repository and build the Docker image:

    ```sh
    docker build -t cdr2svg .
    ```

2. Running the Conversion

    To convert a CorelDRAW file (sample.cdr) to SVG:

    ```sh
    docker run --rm -v $(pwd):/data cdr2svg cdr2svg /data/sample.cdr > output.svg
    ```

    - `-v $(pwd):/data`: Mounts your current working directory into the container at /data.
    - `cdr2svg /data/sample.cdr`: Specifies the CorelDRAW file within the mounted directory.
    - `> output.svg`: Redirects the SVG output to your local directory.

## Included Libraries

This tool relies on the following libraries, which are bundled into the Docker image to ensure compatibility and long-term accessibility:

- [**libcdr**](git://gerrit.libreoffice.org/libcdr): Parses CorelDRAW file formats and provides the backbone for file processing.
- [**librevenge**](git://git.code.sf.net/p/libwpd/librevenge): Provides utilities for interpreting and generating vector graphic formats. Includes librevenge-generators and librevenge-stream modules.

The Docker image automatically clones and builds these libraries during the build process.

## Modifications

This project is based on the original cdr2xhtml tool but has been modified to:

1.Output SVG content directly rather than XHTML with embedded SVG.
2.Simplify and adapt the tool for modern workflows.
3.Package it into a portable Docker image.

The source code for cdr2svg is located in src/cdr2svg.cpp within the repository.

## Licensing

The cdr2svg tool is distributed under the Mozilla Public License, v. 2.0. You can find the license text at <http://mozilla.org/MPL/2.0/>.

The bundled libraries are licensed as follows:

- **libcdr**: Mozilla Public License v. 2.0
- **librevenge**: Mozilla Public License v. 2.0

For more details, refer to the individual library repositories listed above.

Reporting Issues

If you encounter any issues or have feature requests, you can:

1. Open an issue on this GitHub repository.
2. Report bugs related to libcdr or librevenge at the LibreOffice Bug Tracker.

Acknowledgements

We extend our gratitude to the authors and maintainers of the libcdr and librevenge libraries for their exceptional open-source contributions, which make this tool possible.

For any additional information, feel free to open a discussion or submit a pull request.
