﻿// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

// 미리 컴파일된 헤더를 사용하는 경우 컴파일이 성공하려면 이 소스 파일이 필요합니다.

// 미리 컴파일된 헤더 :
// 프로그램 전체에서 사용해야 할 헤더가 너무 많을 경우
// 프로그램을 실행할 때마다(컴파일할 때마다) 시간이 너무 오래 걸리게 되는 문제가 있음
// 이런 시간 소모를 막기 위해, 처음에 컴파일할 때 아예 이 헤더 부분만을 따로 컴파일한 결과물을
// 파일로서 저장해서, 앞으로 컴파일할 때마다 새로 이 헤더를 컴파일하는 대신
// 미리 컴파일해서 만들어둔 파일을 불러와서 컴파일에 이용하는 개념
// -> .pch 파일

// 원래대로라면 프로젝트에서 C/C++ -> 미리 컴파일된 헤더 부분에서 설정을 해주고
// 그 설정에 맞게 파일을 만들어주고 헤더와 cpp 파일을 구성해주면 완성되는데
// VS가 설치된 PC에 따라선 이게 안 되는 경우가 있음
// 따라서, 처음에 프로젝트를 만들 때부터 아예 미리 컴파일된 헤더에 체크해서 만들어둔 것을
// 우리가 고쳐 이용하는 식으로 하는 것이 오류가 발생할 여지가 제일 적음
// 이 때문에 프로젝트를 처음에 만들 때 windows 데스크톱 마법사를 이용해 작성했던 것

// 추가로, 이 pch 파일 및 헤더의 이름은 VS 버젼마다 다르므로 생성된 것이 다르다고 당황하지 말 것

// 마지막으로, 미리 컴파일된 헤더 사용시 프로젝트가 다음과 같이 설정되어있어야 함
// 1. 프로젝트 속성 -> C/C++ -> 미리 컴파일된 헤더의 2개 값이 다음과 같이 설정
// 미리 컴파일된 헤더 : 사용, 미리 컴파일된 헤더 파일 : pch.h
// (정확히는 파일명은 미리 컴파일된 헤더로서 사용할 헤더의 이름과 일치하면 됨)
// 2. 해당 헤더와 같은 이름의 .cpp 파일의 속성 -> C/C++ -> 미리 컴파일된 헤더의 2개 값
// 미리 컴파일된 헤더 : 만들기, 미리 컴파일된 헤더 파일 : pch.h

// 미리 컴파일된 헤더를 사용할 경우,
// 이 헤더에 포함시킬 헤더들은 그 헤더의 .cpp 파일에
// 미리 컴파일된 헤더를 반드시 include시켜야 정상적으로 작동함
// 대신, 지금까지의 프로그램에선 자기 자신의 헤더를 포함시켜야 정상 작동했지만
// 여기선 자기 자신을 포함시키지 않아도 됨