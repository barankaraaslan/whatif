set -e

cd ..
mvn clean install
cd examples
cd log4cpp
mvn clean install
cd ..
cd alien
mvn clean install
cd ..