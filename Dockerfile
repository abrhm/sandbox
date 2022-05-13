FROM silkeh/clang:14
# Add the src folder to the image
ADD src /home/src
# Add CMake to the image
ADD CMakeLists.txt /home/
# Build the source
RUN cd /home && cmake . && make
# Execute the binary on docker run
CMD [ "/home/example" ]
