
##Building

~~~
mkdir build
cd build
cmake ..
make
~~~

##Running the unit tests

~~~
cd build && make test
~~~

##Running the programm

~~~
cd build && ./main/vcfFilter -in ~/Downloads/sample.vcf -out ~/Downloads/sample_filtered.vcf -filter "AF > 0.5"
~~~

The filter expression is composed of `<variable name> <boolean op> <float value>` which will apply on the INFO column. Currently, the supported operators are `<`, `<=`, `==`, `>`, `>=`.