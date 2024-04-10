version="0.0.5"
tag="779965382548.dkr.ecr.us-east-1.amazonaws.com/sro/game:${version}"
docker build -t sro-gameserver -f prodServer.Dockerfile .
docker tag sro-gameserver $tag
docker push $tag
