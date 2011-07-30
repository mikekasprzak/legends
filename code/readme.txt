
setup.sh   - Initialize this source tree for use

sku.sh     - Manage and change the current product SKU

content.sh - Manage, update, and checkout content files

makefile   - standard GNU make build script (invoke using "make")

commit.sh  - performs an SVN commit across all trees (Content, Custom, and Current), takes a message as argument
update.sh  - performs an SVN update across all trees (Content, Custom, and Current)

todo.txt   - Text file todo list. May not be up to date with Mike's list.

readme.txt - This file

--------------------------------------------------------------------------------

Config/  - Current configuation details

Content/ - Art, Sound, Music, Scripts. All files that aren't code, per project.

Custom/  - Files and SKU files, unique per game. (NOTE: setup.sh checks this out)
Target/  - Files that are unique per platform. All platforms for all targets.

obj/     - garbage files go here during building
output/  - executable binaries and "to be packaged" app folders go here

src/     - source code

Tools/   - Addition shell scripts and command line tools used by the build system

--------------------------------------------------------------------------------

Content/Tools/       - If needed, tools for converting files (you can take pre-converted content)

Content/Art/...      - Root folders.
Content/Sound/...    -
Content/Music/...    -
Content/Scripts/...  - 

Content/Art/src/     - Sources.
Content/Sound/WAV/   -
Content/Music/WAV/   -
Content/Scripts/src/ -

Content/Art/4444/    - Defaults.
Content/Sound/WAV/   -
Content/Music/OGG/   -
Content/Scripts/src/ -
