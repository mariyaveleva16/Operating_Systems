find ~ -mindepth 1 -maxdepth 1 -user $(whoami) -type f -print0|xargs -0 chmod 775 2>/dev/null
