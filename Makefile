# Copyright (C) 2014-2019  Peniel Vargas <tsuneake.kaemitsu@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.
CPPFLAGS := -std=c++11
BINNAME := hiden
LANGS := ja
LOCALEDIR := locale
POTFILE := ${LOCALEDIR}/${BINNAME}.pot
POFILES := ${addprefix ${LOCALEDIR}/,${addsuffix .po,${LANGS}}}
POTEMPFILES := ${addprefix ${LOCALEDIR}/,${addsuffix .po~,${LANGS}}}
MOFILES = ${POFILES:.po=.mo}

default: build

build:
	g++ ${CPPFLAGS} -o ${BINNAME} ${BINNAME}.cpp
	
locale: ${MOFILES}

${POTFILE}:
	xgettext --language=C++ --add-comments --sort-output \
	--default-domain=${BINNAME} --from-code=UTF-8 --keyword=_ \
	--output=$@ ${BINNAME}.cpp

${LOCALEDIR}/%.po: ${POTFILE}
	msginit --locale=$* --no-translator --input=$< --output=$@
	msgmerge --update $@ $<

%.mo: %.po
	msgfmt -o $@ $<

clean:
	@rm -f ${BINNAME} ${LOCALEDIR}/*.mo

.PHONY: clean ${POTFILE}
.PRECIOUS: ${LOCALEDIR}/%.po
