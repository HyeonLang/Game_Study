#pragma once
/*
	이번 주 과제 : 그래픽 파이프라인에 대해 설명하는 것중 간략하게 설명한 부분에대해 따로 조사

	1. 그래픽 파이프라인
		- DirectX에서 그래픽을 화면에 출력하기 위해 거치는 일련의 과정

		- 파이프라인 : 프로그래밍에서 한 데이터를 처리하면, 그 데이터를 처리하며 나온 출력을 다음 단계에 이용하는것을 
						반복하여 정해진 여러 단계를 전부 거쳐 원하는 결과를 도출해내는 과정
						ex) 1. 코드 짜기
							2. 코드와 쓰이는 자료들을 링커가 연결한다.
							3. 링커가 연결한 주소 등을 토대로 컴파일링 한다.
							... 등의 일련의 과정을 거친다. 이 단계 각각이 파이프라인의 한 단계

		- 그래픽 역시 마찬가지로 최종적으로 직접 출력하도록 하는 과정

		그래픽 파이프라인 단계 : https://learn.microsoft.com/ko-kr/windows/win32/direct3d11/overviews-direct3d-11-graphics-pipeline

		- DX 버전에 따라 파이프라인의 단계가 달라질 수 있음
		(DX 11 기준)
		0. 코딩 및 자료준비 과정 (Input-Assembler Stage)

		1. 정점 셰이더를 이용한 처리
			- 입력에서 아무 처리도 되어있지 않은 각 정점들의 정보를 그래픽 출력에 필요한 형태로 가공 단계
			- DirectX는 3D를 다룸. 3D에선 시점이 필요하다.  Vertex Shader는 입력한 3D 공간의 좌표계들을 
				"시점 기준의 좌표계"로 변환하는 과정을 거친다.

		2. 테셀레이션 단계 (Tessellation)
			- 위의 정점 셰이더에서 넘어온 도형들을 쪼개서 그래픽을 쉽게 표현할 수 있도록 최소단위로 나누는 단계
			- 3D에선 그래픽이 폴리곤의 집합, 도형들을 시스템에서 소화하기 쉽도록 더 잘게 쪼개준다.
			- 실제로는 Hull Shader, Tesselation, Domain Shader, Geometry Shader 등의 여러 단계를 거쳐 진행된다.

		3. 레스터라이저 단계 (Rasterizer)
			- 벡터로 이루어진 정점들로 만들어진 도형들을 픽셀 단위로 분해하는 단계

		4. 픽셀 셰이더 (Pixel Shader)
			- 픽셀 단위로 쪼개진 그래픽에 픽셀 단위로 색을 입히는 단계.

		5. 출력 단계 (Output)


*/

/*
	1.	Input-assembler stage
				↓
	2.	Vertex Shader stage
				↓
	3.	Hull Shader stage
				↓
	4.	Tessellator stage
				↓
	5.	Domain Shader stage
				↓
	6.	Geometry Shader stage
				↓
	7.			→ → → → → →  Stream Output stage
				↓
	8.	Rasterizer stage
				↓
	9.	Pixel-Shader stage
				↓
	10.	Ouput-Merger stage
			

	그래픽 파이프라인이란?
	- 3차원 컴퓨터 그래픽스에서 그래픽스 파이프라인 또는 렌더링 파이프라인은 3차원 이미지를
	  2차원 래스터 이미지로 표현을 하기위한 단계적인 방법.

	

	1.	Input-assembler stage (입력 어셈블러 단계)
	- user-filled buffer로부터 원시 데이터를 읽어들여 그 후 파이프라인 단계에서 사용될 
	  primitive types(line list, triangle strips 등등)데이터로 assemble하는 역할을 수행한다.

	2.	Vertex Shader stage (정점 셰이더 단계)
	- input assembler 단계를 통과한 vertices들을 처리하는 단계.
	- transformation, skinning, morphing, and per-vertex lighting과 같은 작업을 수행
	- vertex shader는 단일 input vertex을 받고 output으로 단일 vertex를 출력한다.

	(테셀레이션 단계)
	3.	Hull Shader stage 
	- DirectX11은 테셀레이션(GPU에서 low-detail subdivision surface를 higher-detail primitves로 바꾸는)을
	  구현하기 위한 3가지의 새로운 단계를 서포트한다.
	- Hull shader, tesselator, domain shader 단계가 3가지의 단계에 포함된다.

	4.	Tessellator stage 
	- 도메인(quad, tri or line)을 더 많고 작은 오브젝트(triangles, points or lines)로 잘게 나누는 작업을 수행한다.

	5.	Domain Shader stage 
	- 잘게 나누어진 포인트의 vertex position를 계산하는 단계.

				Hull Shader
			Output Control Points	→ → → ↘	
												→ → → Domain Shader → → → Vertex Position
				Tessellator Stage	→ → → ↗ 
			Output Texture Coordinates

	6.	Geometry Shader stage (기하 도형 셰이더 단계)
	- 정점을 input으로 받아 application-specified 셰이더를 적용하고 생성된 정점들을 출력한다.
	- vertex shader와는 다르게 기하셰이더는 입력으로 full primitive의 정점을 받는다. 
	  기하셰이더는 edge 인접 원시 데이터들을 입력받을 수 있다.

	7.	Stream Output stage (스트림 출력 단계)
	- 기하 셰이더단계(또는 정점셰이더 단계)에서 메모리에 있는 하나 이상의 버퍼로 정점 데이터를 연속적으로 
	  출력하는 단계. 
	- 메모리에 출력된 데이터들은 pipeline에서 다시 읽어들일 수 있다.

	8.	Rasterizer stage (래스터 라이저 단계)
	- vector 정보를 래스터 이미지(Pixel)로 변환하는 단계

	9.	Pixel-Shader stage (픽셀 셰이더 단계)
	- 픽셀 라이팅이나 post-processing과 같은 쉐이딩을 가능하게하는 단계

	10.	Ouput-Merger stage (출력 병합기 단계)
	- 최종출력되는 픽셀의 색상을 생성한다. 블렌딩 단계
	- depth/stencil 테스트를 수행하여 실제로 렌더링여부를 결정하고 최종색상을 blend한다.
*/
