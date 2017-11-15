#!/usr/bin/env bash
cmake . && make && mv Editor cmake-build-debug/Editor && mv Client cmake-build-debug/Client && mv Server cmake-build-debug/Server && mv SoundTest cmake-build-debug/SoundTest && mv Test cmake-build-debug/Test
