#include "Replicator.h"

Replicator::Replicator()
{

}

//Probuje wystarotwac replikacje
// jesli sie uda oznacza to ze jest jest glowna kopia wirusa
// jesli nie to ta kopia powstala w wyniku zarazenia i czeka na nowa ofiare
STATE Replicator::Start()
{

    return NOWORK;
}
