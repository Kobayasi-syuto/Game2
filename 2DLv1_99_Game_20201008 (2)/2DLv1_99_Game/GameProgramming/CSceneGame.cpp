#include "CSceneGame.h"
#include "CTexture.h"
#include "CMap.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"

void CSceneGame::Init() {
	//�V�[���̐ݒ�
	mScene = EGAME;

	Texture.Load("Image.tga");
	//�����摜�̓ǂݍ���
	CText::mFont.Load("font.tga");

	//�N���X�̃����o�ϐ��ւ̑��
	CPlayer *Player = new CPlayer();
	Player->x = 150;
	Player->y = 150;
	Player->w = 25;
	Player->h = 25;
	Player->mEnabled = true;

	int map[8][9] =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1,1},
		{ 0, 0, 0, 0, 0, 0, 0, 0,1},
		{ 1, 0, 1, 1, 1, 0, 1, 0,1},
		{ 1, 0, 1, 0, 0, 1, 0, 1,1},
		{ 1, 0, 1, 1, 0, 0, 0, 0,1},
		{ 1, 0, 0, 0, 1, 0, 1, 0,1},
		{ 1, 0, 1, 0, 0, 0, 1, 0,0},
		{ 1, 1, 1, 1, 1, 1, 1, 1,1},
	};

	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 9; i++) {
			//map�̗v�f��1�̎��A�l�p�`�z�u
			if (map[j][i] == 1) {
				CMap *Map = new CMap();
				//�l�p�`�ɒl��ݒ�
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
			}
			else if (map[j][i] == 2) {
				CEnemy *Enemy = new CEnemy();
				Enemy->x = i * 100 - 350;
				Enemy->y = j * -100 + 250;
				//�E�ֈړ�
				Enemy->mFx = 0;
				Enemy->mFy = 1;
			}
		}
	}
}

void CSceneGame::Update() {
	/*
	�z��̗v�f���J��Ԃ�
	�z��.size()
	�z��̗v�f�����擾����
	*/
	for (int i = 0; i < VectorRect.size(); i++) {
		/*
		�z��̎Q��
		�z��[�Y����]
		�ʏ�̔z�񓯗l�ɓY�����ŗv�f�ɃA�N�Z�X�ł���
		*/
		//�X�V����
		VectorRect[i]->Update();
	}
	for (int i = 0; i < VectorRect.size() - 1; i++) {
		//�Փˏ���
		for (int j = i + 1; j < VectorRect.size(); j++) {
			VectorRect[i]->Collision(VectorRect[i], VectorRect[j]);
			VectorRect[j]->Collision(VectorRect[j], VectorRect[i]);
		}
	}

	//���X�g����폜����
	//�C�e���[�^�̐���
	std::vector<CRectangle*>::iterator itr;
	//�C�e���[�^��擪
	itr = VectorRect.begin();
	//�Ō�܂ŌJ��Ԃ�
	while (itr != VectorRect.end()) {
		if ((*itr)->mEnabled) {
			//����
			itr++;
		}
		else {
			//false�̃C���X�^���X���폜
			delete *itr;
			//���X�g������폜
			itr = VectorRect.erase(itr);
		}
	}

	for (int i = 0; i < VectorRect.size(); i++) {
		//�`�揈��
		VectorRect[i]->Render();
	}
	//�`��͈͕ϐ��̍쐬�@�͈͉�:-300 �͈͏�:300 �Œ�
	double mLeft, mRigth, mBottom = -300.0, mTop = 300.0;
	//�摜�͈͍��̐ݒ�
	mLeft = CPlayer::spInstance->x - 400.0;
	//�摜�͈͉E�̐ݒ�
	mRigth = mLeft + 800.0f;
	/*�摜�̓��e�ϐ��J�n*/
	//�s��i�ݒ�j���v���W�F�N�V�������[�h�֕ύX
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();//�s��i�ݒ���������j
	//2D�̓��e�͈͂�ݒ�
	gluOrtho2D(mLeft, mRigth, mBottom, mTop);
	for (int i = 0; i < VectorRect.size(); i++){
		//�`�揈��
		VectorRect[i]->Render();
	}
	glLoadIdentity();//�s��i�ݒ�j��������
	//2D�̓��e�͈͂�ݒ�
	gluOrtho2D(-400, 400, -300, 300);
	CText::DrawString("(-380,280)", -380,  280, 16, 16);

}
//���̃V�[���̎擾
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
//�f�X�g���N�^
CSceneGame::~CSceneGame() {
	//�S�ẴC���X�^���X���폜���܂�
	for (int i = 0; i < VectorRect.size(); i++) {
		//�C���X�^���X�̍폜
		delete VectorRect[i];
	}
	//�ϒ��z��̃N���A
	VectorRect.clear();
}