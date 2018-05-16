DOCKER_ID=$(docker run --rm -d -w /home/elfluenza -it debian)
docker cp ./test_bin/ $DOCKER_ID:/home/elfluenza/test_bin/
docker cp ./test_script.sh $DOCKER_ID:/home/elfluenza/test_script.sh
docker attach $DOCKER_ID
#docker rm -v $(docker ps -a -q -f status=exited)
