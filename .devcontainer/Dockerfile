FROM verilator/verilator:v5.048

# Install dev tools
ARG DEBIAN_FRONTEND=noninteractive
USER root
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    python3 \
    python3-pip \
    python3-venv \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Clear entrypoint so it can be used for persistent development and CI steps
ENTRYPOINT []
CMD ["/bin/bash"]
