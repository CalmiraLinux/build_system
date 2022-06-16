install:
	cp ./src/build.py /usr/bin/build_system
	cp ./src/build_pkgs.toml /etc/build_system.toml
	mkdir -pv /usr/share/build_system
	cp ./src/build.sh /usr/share/build_system
	cp ./src/help /usr/share/build_system

remove:
	if [ -f "/usr/bin/build_system" ]; then rm -rf /usr/bin/build_system; fi
	if [ -f "/etc/build_system.toml" ]; then rm -rf /etc/build_system.toml; fi
	if [ -d "/usr/share/build_system" ]; then rm -rf /usr/share/build_system; fi
