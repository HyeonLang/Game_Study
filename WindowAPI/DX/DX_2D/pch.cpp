﻿// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

// 미리 컴파일된 헤더를 사용하는 경우 컴파일이 성공하려면 이 소스 파일이 필요합니다.

// 미리 컴파일된 헤더
// 프로그램 전체에서 사용해야 할 헤더들이 너무 많은 경우
// 매번 프로그램을 컴파일할 때마다 이 헤더들을 하나하나 실시간으로 컴파일하는 건 너무 소모가 많음

// 그래서 이걸 아예 미리 컴파일을 해두고 그 파일을 pch로 만들어서
// 앞으로는 컴파일할 때마다 다시 컴파일하는 대신 해당 파일의 내용을 불러읽는 것

// Visual Studio에서 맨 처음 프로젝트를 만드는 시점부터 미리 컴파일된 헤더를 자동 생성해주는게 아니면
// 속성을 우리가 이거저거 지정을 해줘야 하는데
// 그 지정이 왜인지는 몰라도 실제 프로젝트에 반영이 안 되는 버그가 있음
// (정말 버그가 맞는지는 모르겠는데 솔직히 그거 아니면 어떤 설정을 해도 반영이 안 되는게 설명이 안 됨)

// 그래서 처음부터 마법사를 이용해 프로젝트를 만들고 그렇게 지원된 파일을 이용해서 작업하는게
// 제일 문제가 적은 방법이라 볼 수 있음

// 실제로 지금 새로 만든 프로젝트의 pch.h 파일의 이름을 변경하고 속성도 변경했을 때
// 이게 전혀 반영이 안 되는 걸 확인해서 다시 원래대로 되돌렸음

// 미리 컴파일된 헤더를 사용할 땐
// 그냥 처음부터 프로젝트에서 미리 컴파일된 헤더를 사용하도록 설정해 만들어주고
// 그렇게 주어진 미리 컴파일된 헤더 파일을 수정해서 쓰는 게 제일 안전

// 이러면 해당 헤더파일의 이름을 바꿀 수 없다는 문제가 있긴 한데
// 이건 나중에 필요하면 그 때 이름 바꾸고도 문제가 안 생기는 방법을 찾아보도록 합시다
