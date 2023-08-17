#pragma once

/*
	�� Ʈ��(Tree)
		�� 2���� �ڷᱸ�� -> ���� ����
		�� ����, ����, Ž�� ��� �ؼ��ϴ�. -> ���� �����
		�� Ư�� ���� ���� ���� �ϳ��̴�. -> �������� ���� �׷���
		�� ��ũ�� ������ ����� �������� ������ �ϳ��� ����.

	�� Ʈ�� ��� ����
		�� ���(node) : Ʈ���� �����ϴ� ����
			- ��Ʈ ���(root node)		: Ʈ���� �ֻ��� ���, ������
			- �θ� ���(parent node)		: �ڽ��� ������ ���, �ڽ��� ��ũ�� ���
			- �ڽ� ���(child node)		: �ڽ��� ��ũ�� ���
			- ���� ���(sibling node)	: ���� �θ� ���� ���
			- �ٻ� ���(leaf node)		: �ڽ��� ���� ���, �ܸ� ���(external node)��� �θ��⵵��
			- ���� ���(internal node)	: �ܸ� ��尡 �ƴ� ���

		�� ����(edge)					: ��� ������ ���ἱ, link����� �θ���.
		�� ����(degree)					: �� ��尡 ������ �ڽ��� ����
		�� Ʈ���� ����(degree of tree)	: Ʈ���� �ִ� ����
		�� ����(level)					: ��Ʈ ���κ��� �󸶳� ������ �ִ°�? ���������� root�� 0�ϼ��� �ְ� 1�ϼ��� ����, 0�� ��찡 ����.
		�� ����(Height)					: Ʈ���� �ִ� ����

	�� Ʈ�� ��ȸ
		�� Ʈ���� �� ��带 ��ġ�� �ʰ� � ������ ������ ���ΰ�?
		�� ���� ��ȸ(pre-order)	: root - left - right
		�� ���� ��ȸ(in-order)	: left - root - right
		�� ���� ��ȸ(post-order)	: left - right - root

	�� Ʈ�� ����
		�� ���⼭ ������ root -> 1�� �����Ѵ�.

		�� �� ����Ʈ��(Full Binary Tree)
			���ٻ� ��带 ������ ��� ��尡 �ڽ� ��带 2�� �Ǵ� 0���� ������ Ʈ��

			��I�� ���γ���� ������� ������
				- �ٻ������ ������ I + 1��
				- �� ����� ���� 2I + 1 ��

			�� �� ����Ʈ���� �� N���� ��尡 ������
				- �� ���� ����� ���� (N - 1) / 2
				- �� �ٻ� ����� ���� (N + 1) / 2

			�� �� ����Ʈ���� L���� �ٻ� ��尡 ������
				- �� ����� ���� 2L - 1
				- �� ���� ����� ���� L - 1

		�� ��ȭ ����Ʈ��(Perfect Binary Tree)
			�� �ٻ������ ���̰� ��� ���� �� ������ 2���� �ڽ��� ������ Ʈ��

			�� ���̰� h�϶�
				- �� ����� ���� :2^h - 1

		�� ���� ����Ʈ��(Complete Binary Tree)
			�� ������ ������ ������ ��� �������� ������ ���� �� ����Ʈ��, �ٸ�, ������ ���Եɶ� Ʈ���� ���ʺ��� ä��������.
			�� ���ʴ�� �����͸� ä���ֱ� ������ �� ������ ���� �迭�� �����ϱ⵵ ��
			�� ���̰� h�϶�
				- ����� ���� : 2^(h - 1) ~ 2^h - 1

			�� ����� ������ N�϶�
				- ���� ����Ʈ���� ���̴� ceil(log2(N + 1))

*/