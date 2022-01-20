# Cpp-Based-Simple-3D-Physics-Engine

## 1. 현황
**2021-12-12** 
1) 프로젝트 시작
2) 물리엔진 기초 루틴 설계 (force 적용 -> 위치&가속도 재계산 -> 충돌감지 -> 처리(충돌 오브젝트, 겹치는 오브젝트 등) -> 결과 렌더링)
3) 3D 벡터 객체 연산 정의 및 구현

2021.12.12~ 12.19 : 기말고사 기간으로 프로젝트 일시정지

**2021-12-20**
1) Physics World 구현 (중력 적용)
2) IDE 변경 (CLion -> VS2022)

![image](https://user-images.githubusercontent.com/46223506/146803365-e6c72aa2-a3ef-41e3-b035-a20a40540614.png)

중력 시뮬레이션 결과

**2021-12-21**
1) 충돌 처리 설계   
폐기
   
**2021-12-22 ~ 2022-01-10**
물리 시뮬레이션 렌더링을 위한 OpenGL 학습

**2022-01-10**   
![image](https://user-images.githubusercontent.com/46223506/148786982-a306a8da-907e-45b1-8579-57095c0ed812.png)   
Object class의 데이터를 기반으로 구 렌더링

**2022-01-12**   
![image](https://user-images.githubusercontent.com/46223506/149158898-c2fc7524-8633-44b7-9c66-761d5a346f59.png)   
엔진 기초 설계   
1. 메인 스레드와 물리 스레드를 분리하여 물리 연산을 별도 스레드에서 수행   
2. 렌더링 시 Latest Object Buffer에서 데이터를 가져와 렌더링
3. 만약 Latest Object Buffer가 업데이트 중이라면 대기

**2022-01-14**   
![zx](https://user-images.githubusercontent.com/46223506/149777949-838147f0-79d1-4ea5-b2aa-3aea06e384be.gif)   
구 오브젝트, 평면 오브젝트 렌더링 및 중력 시뮬레이션   

**2022-01-15**  
충돌 처리 기초 설계   
1. AABB로 충돌 검사 대상 추리기
2. GJK 알고리즘을 활용하여 정밀 검사
3. EPA 알고리즘을 활용하여 충돌 정보 획득 후 오브젝트의 정보 수정   

**2022-01-19**   
충돌 감지 구현(충돌처리 기초 설계의 1-2 구현)   
![zx](https://user-images.githubusercontent.com/46223506/150134210-315397b0-b4d0-40ff-b7b5-f164e03eae64.gif)   

**2022-01-20**   
충돌 정보 획득 및 충돌 반응 테스트
![asdf](https://user-images.githubusercontent.com/46223506/150351992-242cd0c8-e880-4223-be5f-78172e47ac41.gif)   
Position Solver, Impulse Solver 적용   

###### !Issue
1. Frame drop - 오브젝트가 조금만 늘어도 프레임 드랍이 체감되는 수준 => delta time 적용으로 어느 정도 해소
2. Tunneling - 속도가 빠른 물체가 재배치 되거나 delta time이 커지면 물체를 뚫고 지나가는 문제가 있음.
=>AABB를 활용한 CCD 구현을 통해 어느정도 해결 가능 할 것으로 보임

C++ Based 3D Physics Engine
