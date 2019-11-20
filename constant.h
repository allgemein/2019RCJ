#pragma once

//caseを文字で記述するためのenum(数字代わりの文字)を定義
enum phase{
	startRescue,
	rightangleR,
	rightangleL,
	obstacle,
	white,
	Trace,
	passOver
};

enum direction{
	R,
	L,
	F,
	bothSides,
	nothing
};
