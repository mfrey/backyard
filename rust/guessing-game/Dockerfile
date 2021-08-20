FROM rust:1.52 as builder
WORKDIR /usr/src/guessing-game/
COPY . .
RUN cargo build --release
RUN cargo install --path .

FROM debian:buster-slim
# line below only required for additional dependencies
# RUN apt-get update && apt-get install -y extra-runtime-dependencies && rm -rf /var/lib/apt/lists/*
COPY --from=builder /usr/local/cargo/bin/guessing-game /usr/local/bin/guessing-game
CMD ["guessing-game"]
