docker run -it -p 7777 --rm \
  -e SRO_AUTH_CLIENT_ID="sro-gameserver" \
  -e SRO_AUTH_CLIENT_SECRET="BdzZQBDWsUp7mzni6KWRUGYfxsApU6jH" \
  sro-gameserver /Game/SF_Base/Scenes/Scene_Demo -log 
  # --entrypoint /bin/bash \
  # sro-gameserver
