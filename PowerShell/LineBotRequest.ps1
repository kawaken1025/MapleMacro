# �p�����[�^�ݒ�
# Line Notify �G���h�|�C���g
$uri    =  "https://notify-api.line.me/api/notify"

# �g�[�N��
$token  = "EmcpAu24UiBeVCSSSL1OW8fKKOY9EjE4vxEjKCYksLz"

# �g�[�N�������N�G�X�g�w�b�_��Authorization�Ɏw��
$header = @{Authorization=$token}

# POST�p�����[�^�Ƀ��b�Z�[�W���w��
$body   = @{message="PowerShell ���� LINE Notify"}

# �����N�G�X�g���s
$res = Invoke-RestMethod -Uri $uri -Method Post -Headers $header -Body $body 

# �f�o�b�O�p���ʕ\��
echo $res