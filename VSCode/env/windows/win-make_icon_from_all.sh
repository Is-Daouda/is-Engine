#!/bin/bash
echo

if [[ $OSTYPE == 'msys' || $OSTYPE == 'win32' ]]; then
	if hash magick 2>/dev/null; then
		read -p "Icon Prefix (\"icon\"): "  icon_prefix
		if [[ $icon_prefix == '' ]]; then
			icon_prefix='icon'
		fi

		output_file=app
		cmd="magick convert ${icon_prefix}_256.png ${icon_prefix}_48.png ${icon_prefix}_32.png ${icon_prefix}_16.png $output_file.ico"
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