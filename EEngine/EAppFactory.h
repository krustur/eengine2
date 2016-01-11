#pragma once

class EApp;

class EAppFactory
{
public:
	EAppFactory();
	virtual ~EAppFactory();

	static EApp *CreateApp();
};

