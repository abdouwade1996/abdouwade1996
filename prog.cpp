#include <iostream>
#include <cmath>

int main()
{
#if 0
    double rhoHydro = 8.99e+7;
    double rhoHelium = 1.786e+8;
    double rhoNoyau = 2.65279e+13;


    TelluricPlanet Terre( 6378, 149597870.7, 365, 5.517e+12 );
    std::cout << "-------------------------------------\n"
              << "Terre:\n"<< Terre << std::endl;
    GazPlanet Jupiter(69911, 778412027, 4332, 71./100,24./100,5./100);
    std::cout << "-------------------------------------\n"
              << "Jupiter:\n"<< Jupiter << std::endl;


    PlanetarySystem system(2);
    system[0] = new TelluricPlanet( 6378, 149597870.7, 365, 5.517e+12 );
    system[1] = new GazPlanet(69911, 778412027, 4332, 71./100,24./100,5./100);
    std::cout << "mass of planetary system " << system.mass() << " kg" << std::endl;

    system[0]->setAngleInitial(M_PI/3);
    system[1]->setAngleInitial(3*M_PI/5);
    system.setDay( 4500 );
    std::cout << "Planet[0] at day 4500: theta="<< system[0]->theta() << std::endl;
    std::cout << "Planet[1] at day 4500: theta="<< system[1]->theta() << std::endl;

    PlanetarySystem solarSystem = PlanetarySystem::load("solarsytem.txt");
    std::cout << "number of planet in solar system: " <<  solarSystem.nPlanet() << std::endl;
    std::cout << "mass of solar system: " << solarSystem.mass() << " kg" << std::endl;
#endif
    return 0;
}
