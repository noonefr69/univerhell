#include <iostream>
using namespace std;

class pieceOfFabric
{
  public:
    void readSqMeters();
    float toSqYards();
    void displayFabric();
  private:
    float sqMeters;
};

void  pieceOfFabric::readSqMeters()
{
  cout << "Enter size in square meters : ";
  cin >> sqMeters;
}

float pieceOfFabric::toSqYards()
{
  return 1.196 * sqMeters;
}

void pieceOfFabric::displayFabric()
{
  cout << sqMeters << " square meter is " << toSqYards() << " square yards ";
}

int main()
{
  pieceOfFabric fabric;
  fabric.readSqMeters();
  fabric.displayFabric();
  cin.get();
  cin.get();
}
