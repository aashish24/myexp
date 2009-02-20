
#include <NavigatorAdapterBase.h>

NavigatorAdapterBase::NavigatorAdapterBase(void)
    : mNavigator(NULL), mNavMode(NAV_INCREMENTAL)
{
}

NavigatorAdapterBase::~NavigatorAdapterBase(void)
{
}

void
NavigatorAdapterBase::initialize(void)
{
    mNavigator->initialize();
}

void
NavigatorAdapterBase::updateTime(vpr::Interval const &time)
{
    mNavigator->updateTime(time);
}
