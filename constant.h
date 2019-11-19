#pragma once

//caseを文字で記述するためのenumを定義
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
	bothSides,
	nothing
};
