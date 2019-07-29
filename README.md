# 2019학년도 1학기 증강현실(AR)
- 각 프로젝트의 bin/ 내의 opencv_world401d.zip파일은 용량문제로 압축되어 있음. 실행시 압축해제 후 실행

## AR
- ### Practice 1-1
   ![image](https://user-images.githubusercontent.com/7812961/62014375-39f7b500-b1db-11e9-82b1-ffdfe44fd497.png)

   imshow를 이용한 단순 이미지 출력

- ### Practice 1-2
   ![image](https://user-images.githubusercontent.com/7812961/62014411-bee2ce80-b1db-11e9-931d-70f57a8ce06c.png)

   resize 함수를 이용한 크기 조절 및 cvtColor를 이용한 컬러 변환

- ### Practice 1-3
   ![image](https://user-images.githubusercontent.com/7812961/62014495-914a5500-b1dc-11e9-8b97-c5490570e96d.png)

   roi를 이용한 이미지 합성

- ### Practice 1-4
   ![image](https://user-images.githubusercontent.com/7812961/62014508-c0f95d00-b1dc-11e9-93f5-f20379db7bae.png)

   bitwise_xor을 이용한 전경합성

- ### Practice 1-5
   ![image](https://user-images.githubusercontent.com/7812961/62014533-28afa800-b1dd-11e9-857e-0a62060c91bc.png)

   배경 알파처리되어있는 png이미지 전경 합성

- ### Practice 1-6
   VideoCapture를 이용한 웹캠화면 .jpg로 저장

- ### Practice 1-7
   QRCodeDetector를 이용하여 웹캠화면에서 QR코드 인식

- ### Practice 1-8
   QRCodeDetector를 이용해 검출된 정보를 보여지는 웹캠화면상 출력

- ### Practice 1-9
   웹캠화면상에서 QR코드가 검출될 경우 동영상 재생

- ### Practice 1-Final
   웹캠화면상에서 QR코드가 검출될 경우 웹캠화면상에 동영상 증강 후 재생


## AR_2
- ### Practice 2-1
   ![image](https://user-images.githubusercontent.com/7812961/62014866-5f87bd00-b1e1-11e9-9381-cfa72f6c5db6.png)
   ![image](https://user-images.githubusercontent.com/7812961/62014830-ec7e4680-b1e0-11e9-9c0a-92da294fd6c6.png)

   histogram을 이용한 이미지 유사 검색(배경X, 전경의 크기 동일)

- ### Practice 2-2
   ![image](https://user-images.githubusercontent.com/7812961/62014937-13894800-b1e2-11e9-8ba5-3985074631d5.png)
   ![image](https://user-images.githubusercontent.com/7812961/62014902-d1f89d00-b1e1-11e9-9595-8ba063573d53.png)

   histogram을 이용한 이미지 유사 검색(배경O, 전경의 크기 상이)

- ### Practice 2-3
   ![image](https://user-images.githubusercontent.com/7812961/62015014-b641c680-b1e2-11e9-93f8-6686c4c951eb.png)
   ![image](https://user-images.githubusercontent.com/7812961/62015037-e4bfa180-b1e2-11e9-9458-1024d5108cd1.png)

   cornerHarris를 이용한 엣지 검출

- ### Practice 2-4
   ![image](https://user-images.githubusercontent.com/7812961/62015106-92cb4b80-b1e3-11e9-96a7-fdafd230d933.png)
   ![image](https://user-images.githubusercontent.com/7812961/62015116-b42c3780-b1e3-11e9-996a-07bae3e789a0.png)

   GaussianBlur를 이용한 Blur

- ### Practice 2-5
   ![image](https://user-images.githubusercontent.com/7812961/62015183-1be28280-b1e4-11e9-957f-aa60bfb19b5a.png)

   SIFT를 이용한 Keypoints 검출

- ### Practice 2-6
   ![image](https://user-images.githubusercontent.com/7812961/62015225-88f61800-b1e4-11e9-811a-a0fc1b0a82f8.png)

   각 Keypoint의 벡터값 확인

- ### Practice 3-1
   ![image](https://user-images.githubusercontent.com/7812961/62015314-6e706e80-b1e5-11e9-8b0c-8e9808d283e2.png)

   두개의 이미지에서 keypoints 검출한 뒤 match 결과

- ### Practice 3-2
   ![image](https://user-images.githubusercontent.com/7812961/62015432-8694bd80-b1e6-11e9-930c-b279269fe4f8.png)

   매칭쌍을 이용한 Homography수행

- ### Practice 3-3
   ![image](https://user-images.githubusercontent.com/7812961/62015529-484bce00-b1e7-11e9-80c2-e50f4f143906.png)

   캠 이미지상 검출된 부분에 동영상 증강 재생

- ### Practice 3-4(Final Practice)
   실제 웹캠 영상 속 검출된 부분에 동영상 증강 재생

- ### Practice 3-5
   복수개의 이미지 쿼리를 검출하여 화면에 증강

- ### Practice 4-1
   ORB알고리즘을 이용한 이미지 쿼리 검출


## AR_HW2
- SHIF알고리즘 keypoints 추출
   ![image](https://user-images.githubusercontent.com/7812961/62015787-8f3ac300-b1e9-11e9-9c54-46842be98d9a.png)

- 서로 다른 이미지 간의 keypoint 매칭 결과
   ![image](https://user-images.githubusercontent.com/7812961/62015848-cc9f5080-b1e9-11e9-9839-c8f07ef543d2.png)

- 매칭 결과를 이용한 각 이미지의 호모그라피 결과
   ![image](https://user-images.githubusercontent.com/7812961/62015927-1ee07180-b1ea-11e9-98fb-63ba045f75cb.png)

- 호모그라피를 이용하여 파노라마 생성
   ![image](https://user-images.githubusercontent.com/7812961/62015980-53ecc400-b1ea-11e9-9f20-a5c7892b7423.png)
