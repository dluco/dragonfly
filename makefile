# dragonfly - lightweight webkit browser
# See LICENSE file for license details

export # Export all variables to sub-makes

VERSION = 0.3.0
OUT = dragonfly

DISTFILES = LICENSE makefile README.md TODO data/ src/

PREFIX ?= /usr
MANPREFIX ?= ${PREFIX}/share/man
DATADIR ?= ${PREFIX}/share

all: dragonfly

dragonfly:
	@${MAKE} -C src/
#	For convenience, create link to executable
	@ln -sf src/dragonfly dragonfly

manpage:
	@echo generating manpage
#	Uncomment to update manpage date
#	@sed -r -i "s/\"[0-9]{4}-[0-9]{2}-[0-9]{2}\"/\"$(shell date +%Y-%m-%d)\"/g" data/dragonfly.1
	@sed -r -i "s/dragonfly\\\-([0-9]*\.[0-9]*)*/dragonfly\\\-${VERSION}/g" data/dragonfly.1

desktop:
	@echo generating desktop file
	@sed -r -i "s/Version=[0-9]*\.[0-9]*\.[0-9]*/Version=${VERSION}/g" data/dragonfly.desktop

clean:
	@echo cleaning
	@${RM} ${OUT} dragonfly-${VERSION}.tar.gz
	@${MAKE} -C src/ clean

strip: all
	@echo striping executable
	@${MAKE} -C src/ strip

dist: clean
	@echo creating dist tarball
	@mkdir dragonfly-${VERSION}/
	@cp -r ${DISTFILES} dragonfly-${VERSION}/
	@tar -czf dragonfly-${VERSION}.tar.gz dragonfly-${VERSION}/
	@rm -rf dragonfly-${VERSION}/

install: all strip
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@install -D -m755 src/axon ${DESTDIR}${PREFIX}/bin/axon
	@echo installing desktop file to ${DESTDIR}${DATADIR}/applications
	@install -D -m644 data/axon.desktop ${DESTDIR}${DATADIR}/applications/axon.desktop
	@echo installing colorscheme files to ${DESTDIR}${DATADIR}/axon
	@mkdir -p ${DESTDIR}${DATADIR}/axon/
	@cp -rf colorschemes/ ${DESTDIR}${DATADIR}/axon/
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@install -D -m644 data/axon.1 ${DESTDIR}${MANPREFIX}/man1/axon.1
	@echo installing example configuration file to ${DESTDIR}${PREFIX}/share/doc/axon/axonrc
	@install -D -m644 data/axonrc ${DESTDIR}${PREFIX}/share/doc/axon/axonrc

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/axon
	@echo removing desktop file from ${DESTDIR}${DATADIR}/applications
	@rm -f ${DESTDIR}${DATADIR}/applications/axon.desktop
	@echo removing colorscheme files from ${DESTDIR}${DATADIR}/axon
	@rm -rf ${DESTDIR}${DATADIR}/axon/colorschemes/
	@echo removing program data directory
	@rm -rf ${DATADIR}/axon
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/axon.1
	@echo removing example configuration file from ${DESTDIR}${PREFIX}/share/doc/axon/axonrc
	@rm -f ${DESTDIR}${PREFIX}/share/doc/axon/axonrc
	@echo removing program documentation directory
	@rm -rf ${DESTDIR}${PREFIX}/share/doc/axon/

.PHONY: all dragonfly manpage clean dist install uninstall
