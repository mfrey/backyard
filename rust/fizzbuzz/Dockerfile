FROM rust:1.52 as builder
WORKDIR /usr/src/fizzbuzz/
COPY . .
RUN cargo build --release
RUN cargo install --path .

FROM debian:buster-slim
# line below only required for additional dependencies
# RUN apt-get update && apt-get install -y extra-runtime-dependencies && rm -rf /var/lib/apt/lists/*
COPY --from=builder /usr/local/cargo/bin/fizzbuzz /usr/local/bin/fizzbuzz
CMD ["fizzbuzz"]
