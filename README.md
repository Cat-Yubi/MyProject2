# MyProject2
 
 많이 못했습니다..!ㅜㅜ

현재 호출순서

ChatBoxWidget(일반함수, 클라) -> ChatCommunicator(일반함수, 클라) -> ChatCommunicator(서버함수) -> 
ChatManager(서버함수) -> ChatCommunicator(클라함수)

구현과정

    GameMode 역할을 대신해서 ChatManager 만들기
    ChatCommunicator 라는 PlayerController에 붙힐 액터컴포넌트 만들기

이렇게 하게된 이유 :
    GameMode나 후술할 GameState, PlayerController에 이와 관련된 함수를 최소화 하고 싶었습니다
    PlayerController에서 ChatCommunicator를 Public으로 뒀을 뿐 실질적으로 통신을 담당하는 주체는 온전히 컴포넌트에게 일임했습니다

자세한 순서 :
    ChatManager를 GameState 서버에 한번 생성 클라에는 Simulated Proxy로 복제 ( 의문점 1 )
    ChatCommunicator 가 BeginPlay에서 GameState의 ChatManager인스턴스를 가져오고 ChatManager에게 본인인스턴스를 넘겨줌
    ( 의문점 2 )
 
    ChatBox 위젯이 Controller의 함수를 호출하는것이 아닌 ChatCommunicator 에게 직접 접근해서 함수를 호출함
    그러면 ChatCommunicator는 본인의 서버함수를 통해 서버로 올라가고 거기서 ChatManager의 서버함수를 호출함
    (일반함수로 해도 되지 않나라는 소소한 의문점이..)

    ChatManager는 판단후 ChatCommunicator의 클라함수를 호출
    
-----------------------------------
 의문점 1 
 {
    아직 의문점이 드는게 GameState에서 Replicated를 했는데 어차피 서버에 한번만 생성한 Manager고
    클라의 ChatManager 인스턴스는 어차피 서버함수를 호출할 권한이 없다고 생각드는데 맞나요? 
    요지는 복제할 필요도 없이 서버에만 둬도 상관없지 않나.. 라는 궁금점이 있습니다 
 }
 
 의문점 2
 {
    나중에 매번 가져오기 불필요하다 생각되서 선택했습니다
    하지만 서버는 바로 아는 반면 클라이언트는 모르기에 GameState에 복제가 완료되는 시점에 델리게이트를 통해 인스턴스를 직접 넘겨줍니다

    하지만 의문점1 과 이어서 또 생각이 듭니다 어차피 ChatCommunicator의 함수를 직접 호출하는건 Widget이고
    ChatManager에 접근할려면 클라에서 직접접근이 아니라 서버에서 접근해야되는데 이러면 사실
    ChatCommunicator는 서버에서만 ChatManager의 인스턴스를 알고 있고 클라에서는 nullptr이여도 상관없지 않을까.. 하는 의문이 남았습니다

    위와 같은 생각이 남아 외부에서 접근하는 Public으로 둔 함수에선 ChatManager의 인스턴스를 쓸수 없게 해놨습니다.

    이렇게 서버함수에서만 ChatManager 인스턴스를 쓴다하여도 이건 잠재적 위험요소라는 생각도 남게되고..
    이럴거면 그냥 함수내에서 매번 GetGameState로 인스턴스를 가져오는게 맞지않나 싶기도 합니다..(불러오는데 캐스팅을 하는것도 아니기도 하고..) 튜터님의 의견이 궁금합니다!
 }