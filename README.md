# BÁO CÁO PHÂN TÍCH VÀ THIẾT KẾ PHÂN HỆ QUYẾT TOÁN ĐƠN HÀNG SHOPEEFOOD BẰNG C

> 👤 **Học viên:** Hoàng Công Dũng | **Mã SV:** PTIT-HCM-009
> 🏫 **Môn học:** it102-rl-hoangcongdung

---

## 📊 Sơ đồ thiết kế hệ thống (Activity Diagram)

> 💡 *Sơ đồ dưới đây được render tự động trực tiếp trên GitHub bằng Mermaid. Bạn cũng có thể tải file **`bt2.drawio`** trong repository này để mở và chỉnh sửa trực tiếp trên [Draw.io (diagrams.net)](https://app.diagrams.net).* 

```mermaid
graph TD
  Start([Bắt đầu chương trình]) --> Input[Nhập thông tin đơn hàng: ID, giá, số lượng, khoảng cách, giờ cao điểm, trạng thái quán, tồn kho, loại tài khoản]
  Input --> CheckBuffer[Xử lý bộ đệm stdin chống trôi lệnh %c]
  CheckBuffer --> CheckValid{Kiểm tra tính hợp lệ cơ bản: Open==1, Stock>=Qty, Qty>0, Price>0}
  CheckValid -- Không hợp lệ (0) --> SetZero[Gán toàn bộ phí và Tổng thành tiền = 0.00 VNĐ]
  CheckValid -- Hợp lệ (1) --> CalcSub[Tính Subtotal = Price * Qty và Base Ship = Distance * 5000.0]
  CalcSub --> CheckFreeship{Kiểm tra Freeship: (Subtotal >= 100000 && Distance <= 5.0) || Account == 'V'}
  CheckFreeship -- Thỏa mãn --> ApplyDiscount[Giảm giá Freeship = 15000.0]
  CheckFreeship -- Không thỏa mãn --> NoDiscount[Giảm giá Freeship = 0.0]
  ApplyDiscount --> CalcPeak[Tính phụ phí giờ cao điểm = 10000.0 * PeakStatus]
  NoDiscount --> CalcPeak
  CalcPeak --> CalcFinal[Tính Tổng thành tiền = Subtotal + Base Ship - Freeship + Peak Surcharge]
  SetZero --> PrintResult[In báo cáo hóa đơn ShopeeFood]
  CalcFinal --> PrintResult
  PrintResult --> End([Kết thúc chương trình])
```

---

## Nhiệm vụ 1: Phân tích bài toán I/O và Ràng buộc kỹ thuật

Trong module Checkout Service của ShopeeFood, việc xử lý hàng triệu giao dịch đòi hỏi tốc độ cực cao và sự chính xác tuyệt đối về mặt tài chính. Bài toán đặt ra yêu cầu tính toán toàn bộ hóa đơn mà hoàn toàn không được sử dụng câu lệnh rẽ nhánh if/else hay vòng lặp nào.

Để giải quyết bài toán này, nhóm đã thực hiện ánh xạ toàn bộ dữ liệu đầu vào và đầu ra theo đúng chuẩn yêu cầu kỹ thuật:

- Đầu vào (Input): Mã món ăn (int), Đơn giá (float), Số lượng đặt (int), Khoảng cách giao hàng (float), Trạng thái giờ cao điểm (int), Trạng thái cửa hàng (int), Tồn kho (int), Xếp loại tài khoản (char).
- Đầu ra (Output): Tiền món ăn, Phí giao hàng cơ bản, Số tiền giảm giá Freeship, Phụ phí giờ cao điểm, Trạng thái đơn hàng hợp lệ (0 hoặc 1), và Tổng thành tiền cuối cùng.
- Ràng buộc cốt lõi: Sử dụng đại số Boole và các biểu thức logic (&&, ||, !) để nhân bản kết quả 0 hoặc 1 trực tiếp vào công thức tính tiền nhằm chặn đứng các kịch bản dữ liệu dị biệt.

## Nhiệm vụ 2: Đề xuất giải pháp Đại số Boole và Thiết kế giải thuật

Do yêu cầu không được dùng cấu trúc rẽ nhánh, tư duy thiết kế tập trung vào việc biến các điều kiện logic thành các hệ số nhân (0 hoặc 1) trong công thức toán học.

Cụ thể, biểu thức kiểm tra tính hợp lệ của đơn hàng được xây dựng bằng cách kết hợp các điều kiện: cửa hàng phải mở cửa (is_store_open == 1), tồn kho phải đủ đáp ứng (stock >= quantity), số lượng đặt phải dương (quantity > 0), và đơn giá phải lớn hơn 0 (unit_price > 0).

Tương tự, điều kiện đạt Freeship được biểu diễn bằng phép toán logic kết hợp giữa giá trị đơn hàng, khoảng cách và loại tài khoản khách hàng ('V' hoặc 'N'). Kết quả kiểm tra Freeship (nhận giá trị 0 hoặc 1) sẽ nhân trực tiếp với mức giảm giá 15.000 VNĐ.

- Chặn lỗi bộ đệm stdin: Thêm khoảng trắng trước định dạng %c trong hàm scanf() (ví dụ: scanf(' %c', &account_type)) để triệt tiêu hoàn toàn ký tự xuống dòng '\n' sót lại từ các lệnh nhập số trước đó.
- Xử lý kịch bản dị biệt: Khi đơn hàng không hợp lệ (ví dụ quán đóng cửa hoặc hết hàng), biểu thức hợp lệ trả về 0, nhân với tổng tiền sẽ lập tức ép kết quả thanh toán cuối cùng về đúng 0.00 VNĐ.
- Đảm bảo không vi phạm ràng buộc: Toàn bộ quá trình tính toán diễn ra tuần tự thông qua biểu thức số học thuần túy.

## Nhiệm vụ 3: Bảng đặc tả chi tiết quy trình xử lý đơn hàng

Bảng dưới đây mô tả tuần tự các bước xử lý dữ liệu từ lúc tiếp nhận thông tin đầu vào đến khi xuất ra báo cáo hóa đơn hoàn chỉnh trên console:

| Bước | Thực thể / Module | Thao tác nghiệp vụ | Biểu thức / Điều kiện xử lý |
| --- | --- | --- | --- |
| 1 | Hệ thống I/O | Tiếp nhận dữ liệu đầu vào từ người dùng | scanf() với xử lý bộ đệm chống trôi lệnh char |
| 2 | Bộ lọc Hợp lệ | Kiểm tra trạng thái cửa hàng, tồn kho và tính hợp lệ của số lượng/đơn giá | valid = (store == 1) && (stock >= qty) && (qty > 0) && (price > 0) |
| 3 | Tài chính cơ bản | Tính tiền món ăn và phí giao hàng cơ bản | subtotal = price * qty; base_ship = distance * 5000.0 |
| 4 | Chính sách Freeship | Kiểm tra điều kiện nhận ưu đãi miễn giảm giao hàng | freeship_cond = ((subtotal >= 100000.0) && (distance <= 5.0)) || (account == 'V') |
| 5 | Phụ phí giờ cao điểm | Tính toán phụ phí dựa trên trạng thái khung giờ | peak_fee = 10000.0 * peak_status |
| 6 | Tổng quyết toán | Tính tổng tiền thanh toán cuối cùng nhân với hệ số hợp lệ | final_amount = (subtotal + base_ship - (15000.0 * freeship_cond) + peak_fee) * valid |
| 7 | Xuất báo cáo | In phiếu hóa đơn chi tiết chuẩn ShopeeFood ra màn hình | printf() định dạng chuẩn 2 chữ số thập phân |

## Nhiệm vụ 4: Triển khai Mã nguồn C và Kiểm thử kịch bản

Mã nguồn được viết hoàn chỉnh bằng ngôn ngữ C, biên dịch thành công 100% bằng gcc mà không phát sinh bất kỳ cảnh báo (warning) hay lỗi nào. Toàn bộ logic code tuân thủ tuyệt đối giới hạn phạm vi kiến thức đã đề ra.

---

## 📁 Danh sách tệp tin nộp bài trong Repository
- 📝 `bt2.docx`: Báo cáo tài liệu phân tích nghiệp vụ hoàn chỉnh.
- 🎨 `bt2.drawio`: File thiết kế sơ đồ chuẩn theo quy định đề bài (mở trực tiếp bằng [Draw.io](https://app.diagrams.net) hoặc Lucidchart).
- 💻 `main.c`: Mã nguồn chương trình.
