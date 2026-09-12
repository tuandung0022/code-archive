Kỹ thuật đỉnh ảo (virtual node / super source) là một mẹo rất phổ biến trong các bài toán đồ thị, dùng để **biến nhiều điều kiện/nhiều đỉnh đặc biệt thành một điều kiện/một đỉnh duy nhất**, nhờ đó ta có thể áp dụng thẳng một thuật toán chuẩn (MST, BFS, Dijkstra...) mà không cần custom lại thuật toán. Tôi giải thích kỹ cho bạn theo từng khía cạnh nhé.

## 1. Vấn đề gốc là gì?

Trong bài lưới điện ở trên, ta có **k đỉnh nguồn** (nhà máy nối điện chính), và yêu cầu là "mọi đỉnh phải chạm tới **ít nhất một** trong k đỉnh này". Đây là bài toán multi-source — khó áp dụng trực tiếp Kruskal/Prim vì các thuật toán MST chuẩn chỉ làm việc với khái niệm "1 cây khung nối tất cả các đỉnh", không có khái niệm "nối tới 1-trong-nhiều nguồn".

## 2. Ý tưởng của đỉnh ảo

Ta **thêm vào đồ thị một đỉnh không có thật** (gọi là `S`, đỉnh ảo/super source), rồi nối `S` tới toàn bộ k đỉnh nguồn bằng các cạnh có **trọng số 0**.

Sau bước này, đồ thị có (n+1) đỉnh thay vì n, và bài toán "nối n nhà máy tới ít nhất 1 trong k nguồn" được **quy về** bài toán chuẩn: "tìm MST của đồ thị mới, với S là gốc". Vì:

- Cạnh từ `S` tới k nguồn có trọng số 0 → Kruskal luôn ưu tiên chọn chúng đầu tiên (không tốn phí) → coi như toàn bộ k nguồn được "gộp" lại thành 1 thành phần liên thông chung với `S`.
- Sau đó Kruskal tiếp tục chạy bình thường, tự động chọn cạnh rẻ nhất để kéo các đỉnh còn lại vào thành phần liên thông chứa `S` — chính là "kéo điện tới nhà máy gần nguồn rẻ nhất".

Nhờ vậy, thay vì phải nghĩ thuật toán riêng cho bài toán multi-source, ta chỉ cần chạy **MST chuẩn 1 lần** trên đồ thị đã mở rộng.

## 3. Vì sao trọng số phải là 0 (không phải số dương nhỏ, không phải số âm)?

- **Không thể để trọng số dương**, vì như vậy sẽ cộng thêm chi phí "giả" vào tổng chi phí thực — sai đáp số.
- **Không thể để âm**, vì Kruskal dựa trên sắp xếp tăng dần rồi union — nếu có trọng số âm sẽ làm rối logic "cạnh 0 luôn được ưu tiên trước cạnh dương thật", dù về mặt thuật toán Kruskal vẫn đúng nhưng dễ gây nhầm lẫn khi implement, và với Dijkstra cạnh âm sẽ phá vỡ tính đúng đắn của thuật toán hoàn toàn.
- **0 là lựa chọn "trung tính"**: không ảnh hưởng tới tổng chi phí cuối cùng, nhưng vẫn đảm bảo đúng ngữ nghĩa "các nguồn coi như đã được cấp điện sẵn, miễn phí".

## 4. Đây không chỉ dùng cho MST — áp dụng rất rộng

Kỹ thuật đỉnh ảo là một pattern chung, xuất hiện trong nhiều dạng bài khác nhau, tôi liệt kê để bạn hình dung độ phổ biến:

| Bài toán gốc | Cách dùng đỉnh ảo |
|---|---|
| **Multi-source BFS/Dijkstra** (tìm khoảng cách ngắn nhất từ tập nguồn) | Nối đỉnh ảo `S` tới tất cả nguồn, cạnh 0, rồi chạy Dijkstra/BFS 1 lần từ `S` |
| **Multi-sink** (nhiều đích, muốn tìm đường ngắn nhất tới đích gần nhất) | Tương tự nhưng nối các đích vào 1 đỉnh ảo đích chung |
| **Max flow với nhiều nguồn/nhiều đích** (multi-source multi-sink) | Thêm super source nối tới các nguồn (capacity = ∞), thêm super sink nhận từ các đích, rồi chạy max-flow chuẩn 1-nguồn-1-đích |
| **Bài toán ép buộc "chọn ít nhất 1 trong nhóm"** trong quy hoạch động / đồ thị | Gộp nhóm lựa chọn vào 1 đỉnh ảo trung gian |
| **Bài có "trạm trung chuyển ảo"** (ví dụ: sân bay ảo nối các sân bay quốc tế để tính chuyến bay quốc tế rẻ nhất) | Đỉnh ảo đại diện "ra khỏi biên giới", cạnh 0 hoặc phí cố định |

## 5. Điều kiện quan trọng khi dùng

- Đỉnh ảo phải **không tính vào bài toán gốc** — tức là khi kiểm tra kết quả cuối (ví dụ đếm số cạnh trong MST), phải nhớ trừ đi phần đóng góp của đỉnh ảo cho đúng. Trong code ở trên, mình dùng `cnt_edge == n` (không phải `n+1`) chính vì đỉnh ảo chiếm 1 "suất" nối nhưng không tính vào yêu cầu bài toán.
- Trọng số cạnh nối đỉnh ảo phải chọn đúng theo **ngữ nghĩa bài toán** — ở đây là 0 vì nguồn coi như miễn phí, nhưng có bài khác cần trọng số khác (ví dụ multi-sink shortest path đôi khi cần cạnh vô hướng đặc biệt).
- Sau khi thêm đỉnh ảo, đồ thị tăng thêm 1 đỉnh và k cạnh → độ phức tạp gần như không đổi, đây là lý do kỹ thuật này "rẻ" mà cực kỳ hiệu quả.

## Tóm gọn trực giác

Đỉnh ảo giống như việc bạn "gian lận nhẹ" bằng cách tạo ra một điểm trung tâm giả định, biến bài toán nhiều-nguồn/nhiều-đích thành bài toán một-nguồn/một-đích chuẩn — nhờ đó tận dụng được toàn bộ thuật toán kinh điển (Kruskal, Prim, Dijkstra, BFS, Max-flow...) mà không cần phát minh lại thuật toán mới. Đây là một trong những "vũ khí" nên nằm lòng khi làm VNOI, vì nó xuất hiện lặp lại rất nhiều trong các bài multi-source/multi-sink.
