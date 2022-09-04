set -e

cd ..
mvn clean install
cd examples
cd messages
mvn clean install
cd ..
cd log4cpp
mvn clean install
cd ..
cd alien
mvn clean install
cd ..
./alien/target/alien