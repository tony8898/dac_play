These instructions worked on a fresh Ubuntu 14.04 LTS image.

    sudo apt-get update
    sudo apt-get install cmake git libreadline-dev uuid-dev g++ libdb++-dev libdb-dev zip libssl-dev openssl build-essential python-dev autotools-dev libicu-dev libbz2-dev libboost-dev libboost-all-dev
    git clone https://github.com/dacsunlimited/dac_play.git
    cd dac_play
    git submodule init
    git submodule update
    mkdir build&&cd build&&cmake ..
    export LC_ALL="en_US.UTF-8"
    make

For the Qt Wallet, some extra steps are required:

	sudo apt-get install npm qt5-default libqt5webkit5-dev qttools5-dev qttools5-dev-tools nodejs-legacy
	cd dac_play/programs/web_wallet
	sudo npm install -g lineman
	npm install
	cd ../../build
	cmake -DINCLUDE_QT_WALLET=ON ..
	make buildweb
	make BitShares

By default, the web wallet will not be rebuilt even after pulling new changes. To force the web wallet to rebuild, use `make forcebuildweb`.

The binary will be located at programs/client
The wallet can be installed as a local application capable of handling xts: URLs like so:

	sudo cp build/bin/PLAY /usr/local/bin/
	sudo mkdir -p /usr/local/share/icons/
	sudo cp programs/qt_wallet/images/qtapp80.png /usr/local/share/icons/BitShares.png
	sudo mkdir -p /usr/local/share/applications/
	sudo cp programs/qt_wallet/PLAY.desktop /usr/local/share/applications/
