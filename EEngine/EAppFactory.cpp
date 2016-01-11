#include "EAppFactory.h"

#include "EApp.h"

EAppFactory::EAppFactory()
{
}


EAppFactory::~EAppFactory()
{
}

EApp * EAppFactory::CreateApp()
{
	return new EApp();
}
