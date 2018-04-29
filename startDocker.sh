DOCKER_ID=$(docker run --rm -d -w /home/elfluenza -it debian)
docker cp ./setup.sh $DOCKER_ID:/home/elfluenza/setup.sh
docker attach $DOCKER_ID
#docker rm -v $(docker ps -a -q -f status=exited)
