## build image
docker build -t <TAG> .

## run image
docker run -d -p 9453:22 <TAG>

## play
ssh -i id_ed25519 hacker@YOUR_HOST -p 9453