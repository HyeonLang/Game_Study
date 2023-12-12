#pragma once
/*
	�̹� �� ���� : �׷��� ���������ο� ���� �����ϴ� ���� �����ϰ� ������ �κп����� ���� ����

	1. �׷��� ����������
		- DirectX���� �׷����� ȭ�鿡 ����ϱ� ���� ��ġ�� �Ϸ��� ����

		- ���������� : ���α׷��ֿ��� �� �����͸� ó���ϸ�, �� �����͸� ó���ϸ� ���� ����� ���� �ܰ迡 �̿��ϴ°��� 
						�ݺ��Ͽ� ������ ���� �ܰ踦 ���� ���� ���ϴ� ����� �����س��� ����
						ex) 1. �ڵ� ¥��
							2. �ڵ�� ���̴� �ڷ���� ��Ŀ�� �����Ѵ�.
							3. ��Ŀ�� ������ �ּ� ���� ���� �����ϸ� �Ѵ�.
							... ���� �Ϸ��� ������ ��ģ��. �� �ܰ� ������ ������������ �� �ܰ�

		- �׷��� ���� ���������� ���������� ���� ����ϵ��� �ϴ� ����

		�׷��� ���������� �ܰ� : https://learn.microsoft.com/ko-kr/windows/win32/direct3d11/overviews-direct3d-11-graphics-pipeline

		- DX ������ ���� ������������ �ܰ谡 �޶��� �� ����
		(DX 11 ����)
		0. �ڵ� �� �ڷ��غ� ���� (Input-Assembler Stage)

		1. ���� ���̴��� �̿��� ó��
			- �Է¿��� �ƹ� ó���� �Ǿ����� ���� �� �������� ������ �׷��� ��¿� �ʿ��� ���·� ���� �ܰ�
			- DirectX�� 3D�� �ٷ�. 3D���� ������ �ʿ��ϴ�.  Vertex Shader�� �Է��� 3D ������ ��ǥ����� 
				"���� ������ ��ǥ��"�� ��ȯ�ϴ� ������ ��ģ��.

		2. �׼����̼� �ܰ� (Tessellation)
			- ���� ���� ���̴����� �Ѿ�� �������� �ɰ��� �׷����� ���� ǥ���� �� �ֵ��� �ּҴ����� ������ �ܰ�
			- 3D���� �׷����� �������� ����, �������� �ý��ۿ��� ��ȭ�ϱ� ������ �� �߰� �ɰ��ش�.
			- �����δ� Hull Shader, Tesselation, Domain Shader, Geometry Shader ���� ���� �ܰ踦 ���� ����ȴ�.

		3. �����Ͷ����� �ܰ� (Rasterizer)
			- ���ͷ� �̷���� ������� ������� �������� �ȼ� ������ �����ϴ� �ܰ�

		4. �ȼ� ���̴� (Pixel Shader)
			- �ȼ� ������ �ɰ��� �׷��ȿ� �ȼ� ������ ���� ������ �ܰ�.

		5. ��� �ܰ� (Output)


*/

/*
	1.	Input-assembler stage
				��
	2.	Vertex Shader stage
				��
	3.	Hull Shader stage
				��
	4.	Tessellator stage
				��
	5.	Domain Shader stage
				��
	6.	Geometry Shader stage
				��
	7.			�� �� �� �� �� ��  Stream Output stage
				��
	8.	Rasterizer stage
				��
	9.	Pixel-Shader stage
				��
	10.	Ouput-Merger stage
			

	�׷��� �����������̶�?
	- 3���� ��ǻ�� �׷��Ƚ����� �׷��Ƚ� ���������� �Ǵ� ������ ������������ 3���� �̹�����
	  2���� ������ �̹����� ǥ���� �ϱ����� �ܰ����� ���.

	

	1.	Input-assembler stage (�Է� ����� �ܰ�)
	- user-filled buffer�κ��� ���� �����͸� �о�鿩 �� �� ���������� �ܰ迡�� ���� 
	  primitive types(line list, triangle strips ���)�����ͷ� assemble�ϴ� ������ �����Ѵ�.

	2.	Vertex Shader stage (���� ���̴� �ܰ�)
	- input assembler �ܰ踦 ����� vertices���� ó���ϴ� �ܰ�.
	- transformation, skinning, morphing, and per-vertex lighting�� ���� �۾��� ����
	- vertex shader�� ���� input vertex�� �ް� output���� ���� vertex�� ����Ѵ�.

	(�׼����̼� �ܰ�)
	3.	Hull Shader stage 
	- DirectX11�� �׼����̼�(GPU���� low-detail subdivision surface�� higher-detail primitves�� �ٲٴ�)��
	  �����ϱ� ���� 3������ ���ο� �ܰ踦 ����Ʈ�Ѵ�.
	- Hull shader, tesselator, domain shader �ܰ谡 3������ �ܰ迡 ���Եȴ�.

	4.	Tessellator stage 
	- ������(quad, tri or line)�� �� ���� ���� ������Ʈ(triangles, points or lines)�� �߰� ������ �۾��� �����Ѵ�.

	5.	Domain Shader stage 
	- �߰� �������� ����Ʈ�� vertex position�� ����ϴ� �ܰ�.

				Hull Shader
			Output Control Points	�� �� �� ��	
												�� �� �� Domain Shader �� �� �� Vertex Position
				Tessellator Stage	�� �� �� �� 
			Output Texture Coordinates

	6.	Geometry Shader stage (���� ���� ���̴� �ܰ�)
	- ������ input���� �޾� application-specified ���̴��� �����ϰ� ������ �������� ����Ѵ�.
	- vertex shader�ʹ� �ٸ��� ���ϼ��̴��� �Է����� full primitive�� ������ �޴´�. 
	  ���ϼ��̴��� edge ���� ���� �����͵��� �Է¹��� �� �ִ�.

	7.	Stream Output stage (��Ʈ�� ��� �ܰ�)
	- ���� ���̴��ܰ�(�Ǵ� �������̴� �ܰ�)���� �޸𸮿� �ִ� �ϳ� �̻��� ���۷� ���� �����͸� ���������� 
	  ����ϴ� �ܰ�. 
	- �޸𸮿� ��µ� �����͵��� pipeline���� �ٽ� �о���� �� �ִ�.

	8.	Rasterizer stage (������ ������ �ܰ�)
	- vector ������ ������ �̹���(Pixel)�� ��ȯ�ϴ� �ܰ�

	9.	Pixel-Shader stage (�ȼ� ���̴� �ܰ�)
	- �ȼ� �������̳� post-processing�� ���� ���̵��� �����ϰ��ϴ� �ܰ�

	10.	Ouput-Merger stage (��� ���ձ� �ܰ�)
	- ������µǴ� �ȼ��� ������ �����Ѵ�. ���� �ܰ�
	- depth/stencil �׽�Ʈ�� �����Ͽ� ������ ���������θ� �����ϰ� ���������� blend�Ѵ�.
*/
