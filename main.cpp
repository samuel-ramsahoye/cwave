// #include <pybind11/pybind11.h>
// #include <pybind11/stl.h>
// #include <pybind11/numpy.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <vector>

class AiryWave{

public:
    float height;
    float period;
    float depth;
    float length;
    float omega;
    float k = 1e3;

    AiryWave (float height_, float period_, float depth_) : height(height_), period(period_), depth(depth_) {
        compute_wave_length();
    }

    std::vector<float> velocity(float z, float x, float t){
        float u = omega * height / 2 * std::cosh(k * (z + depth)) / std::sinh(k * depth) * std::cos(k*x - omega*t);
        float v = omega * height / 2 * std::sinh(k * (z + depth)) / std::sinh(k * depth) * std::sin(k*x - omega*t);
        std::vector<float> v_vec{u, v};
        return v_vec;
    }
private:
    void compute_wave_length() {
        float g = 9.81;
        float pi = 3.1415;
        omega = 2 * pi / period;
        for(int i = 0; i < 100; i++){
            k = std::pow(omega, 2) / g / std::tanh(k * depth);
        };

        length = 2 * pi / k;
    }

};

int main(){
    AiryWave airy_wave{1.0, 10.0, 20.0};
    std::cout << airy_wave.velocity(-1, 0, 0)[0] << std::endl;
    return 0;
}

// namespace py = pybind11;

// class SomeClass{
//     float multiplier;

// public:
//     SomeClass(float multiplier_) : multiplier(multiplier_) {};
//     float multiply(float input){
//         return multiplier * input;
//     }

//     std::vector<float> multiply_list(std::vector<float> items) {
//         for (auto i = 0; i < items.size(); i++){
//             items[i] = multiply(items.at(i));
//         }
//         return items;
//     }

//     py::tuple multiply_two(float one, float two){
//         return py::make_tuple(multiply(one), multiply(two));
//     }

//     std::vector<std::vector<uint8_t>> make_image(){
//         auto out = std::vector<std::vector<uint8_t>>();
//         for (auto i = 0; i < 128; i++){
//             out.push_back(std::vector<uint8_t>(64));
//         }
//         for (auto i = 0; i < 30; i++){
//             for (auto j = 0; j < 30; j++){
//                 out[i][j] = 255;
//             }
//         }
//         return out;
//     }

//     void set_mult(float val){
//         multiplier = val;
//     }

//     float get_mult(){
//         return multiplier;
//     }

//     void function_that_takes_a_while(){
//         py::gil_scoped_release release;
//         std::cout << "starting fn" << std::endl;
//         std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//         std::cout << "ended fn" << std::endl;

//         py::gil_scoped_acquire acquire;
//         auto list = py::list();
//         list.append(1);
//         list.append(2);
//     }
// };

// SomeClass some_class_factory(float multiplier) {
//   return SomeClass(multiplier);
// }

// float some_fn(float arg1, float arg2) {
//     return arg1 + arg2;
// }

// PYBIND11_MODULE(module_name, handle) {
//     handle.doc() = "This is the module docs.";
//     handle.def("some_fn_for_python", &some_fn);
//     handle.def("some_class_factory", &some_class_factory);
//     py::class_<SomeClass>(
//         handle, "PySomeClass"
//     )
//     .def(py::init<float>())
//     .def("multiply", &SomeClass::multiply)
//     .def("multiply_list", &SomeClass::multiply_list)
//     // .def("multiply_two", &SomeClass::multiply_two)
//     .def("multiply_two", [](SomeClass &self, float one, float two){
//         return py::make_tuple(self.multiply(one), self.multiply(two));
//     })
//     .def_property("multiplier", &SomeClass::get_mult, &SomeClass::set_mult)
//     .def_property_readonly("make_image", [](SomeClass &self){
//         py::array out = py::cast(self.make_image());
//         return out;
//     })
//     .def("function_that_takes_a_while", &SomeClass::function_that_takes_a_while)
//     ;
// }