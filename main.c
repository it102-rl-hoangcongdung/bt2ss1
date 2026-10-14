#include <stdio.h>

int main() {
    int food_id;
    float unit_price;
    int quantity;
    float distance;
    int peak_status;
    int is_store_open;
    int stock_quantity;
    char account_type;

    // Nhập dữ liệu đầu vào từ bàn phím
    printf("Nhap ma mon an: ");
    scanf("%d", &food_id);

    printf("Nhap don gia mon an (VNĐ): ");
    scanf("%f", &unit_price);

    printf("Nhap so lượng dat mua: ");
    scanf("%d", &quantity);

    printf("Nhap khoảng cách giao hàng (km): ");
    scanf("%f", &distance);

    printf("Trang thai khung gio cao diem (1: Co, 0: Khong): ");
    scanf("%d", &peak_status);

    printf("Trang thai cua hang (1: Mo cua, 0: Dong cua): ");
    scanf("%d", &is_store_open);

    printf("So luong mon con trong kho: ");
    scanf("%d", &stock_quantity);

    // Sử dụng khoảng trắng trước %c để chống trôi bộ đệm stdin
    printf("Xep loại tài khoản khach hang (V: VIP, N: Normal): ");
    scanf(" %c", &account_type);

    // Tính toán các giá trị trung gian bằng biểu thức số học
    float subtotal = unit_price * quantity;
    float base_shipping_fee = distance * 5000.0;

    // Kiểm tra điều kiện đạt Freeship (trả về 1 hoặc 0)
    int is_freeship_qualified = ((subtotal >= 100000.0) && (distance <= 5.0)) || (account_type == 'V');
    float freeship_discount = 15000.0 * is_freeship_qualified;

    // Tính phụ phí giờ cao điểm
    float peak_surcharge = 10000.0 * peak_status;

    // Kiểm tra tính hợp lệ của đơn hàng bằng đại số Boole (không dùng if/else)
    int order_validity = (is_store_open == 1) && (stock_quantity >= quantity) && (quantity > 0) && (unit_price > 0);

    // Tính tổng thanh toán cuối cùng, tự động ép về 0 nếu đơn hàng không hợp lệ
    float final_payable_amount = (subtotal + base_shipping_fee - freeship_discount + peak_surcharge) * order_validity;

    // In kết quả hóa đơn thanh toán ShopeeFood chuẩn giao diện yêu cầu
    printf("\n[BẢNG DỮ LIỆU]:\n");
    printf("| ================================================== SHOPEEFOOD ORDER CHECKOUT SYSTEM ==================================================\n");
    printf("Mã món ăn : %d\n", food_id);
    printf("Đơn giá : %.2f VND\n", unit_price);
    printf("Số lượng đặt : %d\n", quantity);
    printf("Khoảng cách giao : %.1f km\n", distance);
    printf("Khung giờ cao điểm : %s (%d)\n", peak_status ? "Có" : "Không", peak_status);
    printf("Trạng thái quán : %s (%d)\n", is_store_open ? "Mở cửa" : "Đóng cửa", is_store_open);
    printf("Số lượng tồn kho : %d\n", stock_quantity);
    printf("Loại tài khoản : %c (%s)\n", account_type, (account_type == 'V') ? "VIP" : "Normal");
    printf("--------------------------------------------------\n");
    printf("TỔNG TIỀN MÓN ĂN : %.2f VND\n", subtotal);
    printf("PHÍ GIAO HÀNG CƠ BẢN: %.2f VND\n", base_shipping_fee);
    printf("GIẢM GIÁ FREESHIP : %.2f VND\n", freeship_discount);
    printf("PHỤ PHÍ GIỜ CAO ĐIỂM: %.2f VND\n", peak_surcharge);
    printf("--------------------------------------------------\n");
    printf("ĐƠN HÀNG HỢP LỆ : %d (1: HỢP LỆ / 0: TỪ CHỐI)\n", order_validity);
    printf("TỔNG THÀNH TIỀN : %.2f VND\n", final_payable_amount);
    printf("================================================== |\n");

    return 0;
}
