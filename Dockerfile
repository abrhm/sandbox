FROM silkeh/clang:14
# Add the src folder to the image
ADD src /home/src
# Build the source
RUN cd /home/src && clang++ -Wall main.cpp -o main
# Execute the binary on docker run
CMD [ "/home/src/main" ]
