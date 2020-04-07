#!/bin/bash
echo

if [[ $OSTYPE == 'msys' || $OSTYPE == 'win32' ]]; then
	if hash magick 2>/dev/null; then
		read -p "Icon Prefix (\"icon_256\"): "  icon_prefix
		if [[ $icon_prefix == '' ]]; then
			icon_prefix='icon_256'
		fi

		output_file=app
		cmd="magick convert ${icon_prefix}.png -define icon:auto-resize=256,96,64,48,32,24,20,16 app.ico"
		echo "$cmd"
		$cmd

		echo
		echo "Successfully created $output_file.ico!"
	else
		echo 'This script requires the "ImageMagick" command-line utility'
		echo 'Download from: https://www.imagemagick.org/script/download.php#windows'
		echo '(Install to default location)'
	fi
else
	echo 'This script should only run in win32'
fi

echo
read -rsn1 -p"Press any key to continue";echo