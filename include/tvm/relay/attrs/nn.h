/*!
 *  Copyright (c) 2018 by Contributors
 * \file tvm/relay/attrs/nn.h
 * \brief Auxiliary attributes for nn operators.
 */
#ifndef TVM_RELAY_ATTRS_NN_H_
#define TVM_RELAY_ATTRS_NN_H_

#include <tvm/attrs.h>
#include <string>

namespace tvm {
namespace relay {

/*! \brief Attributes used in convolution operators */
struct ConvAttrs : public tvm::AttrsNode<ConvAttrs> {
  Array<IndexExpr> strides;
  Array<IndexExpr> padding;
  Array<IndexExpr> dilation;
  int groups;
  IndexExpr channels;
  Array<IndexExpr> kernel_size;
  std::string data_layout;
  std::string weight_layout;
  std::string out_layout;
  DataType out_dtype;

  TVM_DECLARE_ATTRS(ConvAttrs, "relay.attrs.ConvAttrs") {
    TVM_ATTR_FIELD(strides).set_default(Array<IndexExpr>({1, 1}))
        .describe("Specifies the strides of the convolution.");
    TVM_ATTR_FIELD(padding).set_default(Array<IndexExpr>({0, 0}))
        .describe("If padding is non-zero, then the input is implicitly zero-padded"
                  "on both sides for padding number of points");
    TVM_ATTR_FIELD(dilation).set_default(Array<IndexExpr>({1, 1}))
        .describe("Specifies the dilation rate to use for dilated convolution.");
    TVM_ATTR_FIELD(groups).set_default(1)
        .describe("Controls the connections between inputs and outputs."
                  "At groups=1, all inputs are convolved to all outputs."
                  "At groups=2, the operation becomes equivalent to having two convolution"
                  "layers side by side, each seeing half the input channels, and producing"
                  "half the output channels, and both subsequently concatenated.");
    TVM_ATTR_FIELD(channels)
        .describe("The number of output channels in the convolution."
                  " If it is not set, inferred by shape of the weight.")
        .set_default(NullValue<IndexExpr>());
    TVM_ATTR_FIELD(kernel_size)
        .describe("Specifies the dimensions of the convolution window.")
        .set_default(NullValue<Array<IndexExpr> >());
    TVM_ATTR_FIELD(data_layout).set_default("NCHW")
        .describe("Dimension ordering of input data. Can be 'NCHW', 'NHWC', etc."
                  "'N', 'C', 'H', 'W' stands for batch, channel, height, and width"
                  "dimensions respectively. Convolution is applied on the 'H' and"
                  "'W' dimensions.");
    TVM_ATTR_FIELD(weight_layout).set_default("OIHW")
        .describe("Dimension ordering of weight. Can be 'OIHW', 'OIHW16o16i', etc."
                  "'O', 'I', 'H', 'W' stands for num_filter, input_channel, height, and width"
                  "dimensions respectively.");
    TVM_ATTR_FIELD(out_layout).set_default("__undef__")
        .describe("Dimension ordering of output. Can be 'NCHW', 'NHWC', etc."
                  "'N', 'C', 'H', 'W' stands for batch, channel, height, and width"
                  "dimensions respectively. Default to be same as input layout.");

    // use 0 bits to indicate none.
    TVM_ATTR_FIELD(out_dtype)
        .set_default(Int(0))
        .describe("Output data type, set to explicit type under mixed precision setting");
  }
};

/*! \brief Attributes used in softmax operators */
struct SoftmaxAttrs : public tvm::AttrsNode<SoftmaxAttrs> {
  int axis;

  TVM_DECLARE_ATTRS(SoftmaxAttrs, "relay.attrs.SoftmaxAttrs") {
      TVM_ATTR_FIELD(axis).set_default(1)
          .describe("The axis to sum over when computing softmax.");
  }
};

/*! \brief Attributes used in transposed convolution operator */
struct Conv2DTransposeAttrs : public tvm::AttrsNode<Conv2DTransposeAttrs> {
  IndexExpr channels;
  Array<IndexExpr> kernel_size;
  Array<IndexExpr> strides;
  Array<IndexExpr> padding;
  Array<IndexExpr> output_padding;
  Array<IndexExpr> dilation;
  int groups;
  std::string data_layout;
  std::string weight_layout;
  DataType out_dtype;

  TVM_DECLARE_ATTRS(Conv2DTransposeAttrs, "relay.attrs.Conv2DTransposeAttrs") {
    TVM_ATTR_FIELD(channels)
      .set_default(NullValue<IndexExpr>())
      .describe("The dimensionality of the output space"
                "i.e. the number of output channels in the convolution.");
    TVM_ATTR_FIELD(kernel_size)
      .describe("The dimensions of the convolution window.")
      .set_default(NullValue<Array<IndexExpr> >());
    TVM_ATTR_FIELD(strides).set_default(Array<IndexExpr>({1, 1}))
      .describe("The strides of the convolution.");
    TVM_ATTR_FIELD(output_padding).set_default(Array<IndexExpr>({0, 0}))
      .describe("Zero-padding added to one side of the output.");
    TVM_ATTR_FIELD(padding).set_default(Array<IndexExpr>({0, 0}))
      .describe("If padding is non-zero, then the input is implicitly zero-padded"
                "on both sides for padding number of points");
    TVM_ATTR_FIELD(dilation).set_default(Array<IndexExpr>({1, 1}))
      .describe("Specifies the dilation rate to use for dilated convolution.");
    TVM_ATTR_FIELD(groups).set_default(1)
      .describe("Controls the connections between inputs and outputs."
                "At groups=1, all inputs are convolved to all outputs."
                "At groups=2, the operation becomes equivalent to having two convolution"
                "layers side by side, each seeing half the input channels, and producing"
                "half the output channels, and both subsequently concatenated.");
    TVM_ATTR_FIELD(data_layout).set_default("NCHW")
      .describe("Dimension ordering of data. Can be 'NCHW', 'NHWC', etc."
                "'N', 'C', 'H', 'W' stands for batch, channel, height, and width"
                "dimensions respectively. Convolution is applied on the 'H' and"
                "'W' dimensions.");
    TVM_ATTR_FIELD(weight_layout).set_default("OIHW")
      .describe("Dimension ordering of data and weight. Can be 'OIHW', 'OIHW16o16i', etc."
                "'O', 'I', 'H', 'W' stands for num_filter, input_channel, height, and width"
                "dimensions respectively.");
    TVM_ATTR_FIELD(out_dtype)
        .set_default(Int(0))
        .describe("Output data type, set to explicit type under mixed precision setting");
  }
};

/*! \brief Attributes for max pool operator */
struct MaxPool2DAttrs : public tvm::AttrsNode<MaxPool2DAttrs> {
  Array<IndexExpr> pool_size;
  Array<IndexExpr> strides;
  Array<IndexExpr> padding;
  std::string layout;
  bool ceil_mode;

  TVM_DECLARE_ATTRS(MaxPool2DAttrs, "relay.attrs.MaxPool2DAttrs") {
    TVM_ATTR_FIELD(pool_size)
      .describe("Size of the pooling windows.");
    TVM_ATTR_FIELD(strides).set_default(Array<IndexExpr>({1, 1}))
      .describe("Specifies the strides of the convolution.");
    TVM_ATTR_FIELD(padding).set_default(Array<IndexExpr>({0, 0}))
      .describe("If padding is non-zero, then the input is implicitly zero-padded"
                "Padding support both symmetric and asymmetric as"
                "one int : same padding used on all sides"
                "two int : bottom, right will use same padding as top, left"
                "four int : padding width in the order of (top, left, bottom, right)");
    TVM_ATTR_FIELD(layout).set_default("NCHW")
      .describe("Dimension ordering of data and weight. Can be 'NCHW', 'NHWC', etc."
                "'N', 'C', 'H', 'W' stands for batch, channel, height, and width"
                "dimensions respectively. Convolution is applied on the 'H' and"
                "'W' dimensions.");
    TVM_ATTR_FIELD(ceil_mode).set_default(false)
      .describe("When true, will use ceil instead of floor to compute the output shape.");
  }
};

/*! \brief Attributes for avg pool operator */
struct AvgPool2DAttrs : public tvm::AttrsNode<AvgPool2DAttrs> {
  Array<IndexExpr> pool_size;
  Array<IndexExpr> strides;
  Array<IndexExpr> padding;
  std::string layout;
  bool ceil_mode;
  bool count_include_pad;

  TVM_DECLARE_ATTRS(AvgPool2DAttrs, "relay.attrs.AvgPool2DAttrs") {
    TVM_ATTR_FIELD(pool_size)
      .describe("Size of the pooling windows.");
    TVM_ATTR_FIELD(strides).set_default(Array<IndexExpr>({1, 1}))
      .describe("Specifies the strides of the convolution.");
    TVM_ATTR_FIELD(padding).set_default(Array<IndexExpr>({0, 0}))
      .describe("If padding is non-zero, then the input is implicitly zero-padded"
                "Padding support both symmetric and asymmetric as"
                "one int : same padding used on all sides"
                "two int : bottom, right will use same padding as top, left"
                "four int : padding width in the order of (top, left, bottom, right)");
    TVM_ATTR_FIELD(layout).set_default("NCHW")
      .describe("Dimension ordering of data and weight. Can be 'NCHW', 'NHWC', etc."
                "'N', 'C', 'H', 'W' stands for batch, channel, height, and width"
                "dimensions respectively. Convolution is applied on the 'H' and"
                "'W' dimensions.");
    TVM_ATTR_FIELD(ceil_mode).set_default(false)
      .describe("When true, will use ceil instead of floor to compute the output shape.");
    TVM_ATTR_FIELD(count_include_pad).set_default(false)
      .describe("When true, will include padding to compute the average");
  }
};

/*! \brief Attributes for global pool operator */
struct GlobalPool2DAttrs : public tvm::AttrsNode<GlobalPool2DAttrs> {
  std::string layout;

  TVM_DECLARE_ATTRS(GlobalPool2DAttrs, "relay.attrs.GlobalPool2DAttrs") {
    TVM_ATTR_FIELD(layout).set_default("NCHW")
      .describe("Dimension ordering of data and weight. Can be 'NCHW', 'NHWC', etc."
                "'N', 'C', 'H', 'W' stands for batch, channel, height, and width"
                "dimensions respectively. Convolution is applied on the 'H' and"
                "'W' dimensions.");
  }
};


/*! \brief Attributes for dense operator */
struct DenseAttrs : public tvm::AttrsNode<DenseAttrs> {
  IndexExpr units;

  TVM_DECLARE_ATTRS(DenseAttrs, "relay.attrs.DenseAttrs") {
    TVM_ATTR_FIELD(units)
        .describe("Number of hidden units of the dense transformation.");
  }
};


/*! \brief Attributes for upsampling operator */
struct UpSamplingAttrs : public tvm::AttrsNode<UpSamplingAttrs> {
  int scale;
  std::string layout;
  std::string method;

  TVM_DECLARE_ATTRS(UpSamplingAttrs, "relay.attrs.UpSamplingAttrs") {
    TVM_ATTR_FIELD(scale)
        .describe("Should be true to preserve the values at the corner pixels");
    TVM_ATTR_FIELD(layout).set_default("NCHW")
        .describe("Dimension ordering of input data. Can be 'NCHW', 'NHWC', etc."
                  "'N', 'C', 'H', 'W' stands for batch, channel, height, and width"
                  "dimensions respectively. Upsampling is applied on the 'H' and"
                  "'W' dimensions.");
    TVM_ATTR_FIELD(method).set_default("NEAREST_NEIGHBOR")
        .describe("Specify the mode to use for scaling."
                  "NEAREST_NEIGHBOR -  Nearest Neighbor"
                  "BILINEAR - Bilinear Interpolation");
  }
};

/*! \brief Attributes used for the padding operator */
struct PadAttrs : public tvm::AttrsNode<PadAttrs> {
  double pad_value;
  Array<Array<IndexExpr> > pad_width;

  TVM_DECLARE_ATTRS(PadAttrs, "relay.attrs.PadAttrs") {
    TVM_ATTR_FIELD(pad_value).set_default(0.0)
      .describe("Specifies the strides of the convolution.");
    TVM_ATTR_FIELD(pad_width)
      .describe("Number of values padded to the edges of each axis, "
                "in the format of ((before_1, after_1), ..., (before_N, after_N))");
  }
};


/*! \brief Attributes for leaky relu operator */
struct LeakyReluAttrs : public tvm::AttrsNode<LeakyReluAttrs> {
  double alpha;

  TVM_DECLARE_ATTRS(DenseAttrs, "relay.attrs.LeakyReluAttrs") {
    TVM_ATTR_FIELD(alpha).set_lower_bound(0.0).set_default(0.25)
        .describe("Slope coefficient for the negative half axis.");
  }
};


/*! \brief Attributes used in dropout operator */
struct DropoutAttrs : public tvm::AttrsNode<DropoutAttrs> {
  double rate;
  TVM_DECLARE_ATTRS(DropoutAttrs, "relay.attrs.DropoutAttrs") {
    TVM_ATTR_FIELD(rate)
      .describe("Fraction of the input that gets dropped out during training time")
      .set_default(0.5);
  }
};  // struct DropoutAttrs

/*! \brief Attributes used in batch_norm operator */
struct BatchNormAttrs : public tvm::AttrsNode<BatchNormAttrs> {
  int axis;
  double epsilon;
  bool center;
  bool scale;

  TVM_DECLARE_ATTRS(BatchNormAttrs, "relay.attrs.BatchNormAttrs") {
    TVM_ATTR_FIELD(axis)
      .describe("Specify which shape axis denotes the channel.")
      .set_default(1);
    TVM_ATTR_FIELD(epsilon)
      .describe("Small float added to variance to avoid dividing by zero")
      .set_default(1e-5);
    TVM_ATTR_FIELD(center)
      .describe("If True, add offset of beta to normalized tensor. If False, beta is ignored")
      .set_default(true);
    TVM_ATTR_FIELD(scale)
      .describe("If True, multiply by gamma. If False, gamma is not used. "
                "When the next layer is piecewise linear (also, e.g., nn.relu), "
                "this can be disabled since the scaling will be done by the next layer.")
      .set_default(true);
  }
};  // struct BatchNormAttrs


/*! \brief Attributes for LRN operator */
struct LRNAttrs : public tvm::AttrsNode<LRNAttrs> {
  IndexExpr size;
  IndexExpr axis;
  double bias;
  double alpha;
  double beta;

  TVM_DECLARE_ATTRS(LRNAttrs, "relay.attrs.LRNAttrs") {
    TVM_ATTR_FIELD(size).set_default(5)
      .describe("The size of the local region to be considered for normalization.");
    TVM_ATTR_FIELD(axis).set_default(1)
      .describe("Axis of input data layout channel.");
    TVM_ATTR_FIELD(bias).set_default(2)
      .describe("The offset parameter to avoid division by 0.");
    TVM_ATTR_FIELD(alpha).set_default(0.0001)
      .describe("The scaling parameter.");
    TVM_ATTR_FIELD(beta).set_default(0.75)
      .describe("The exponent parameter.");
  }
};


/*! \brief Attributes for L2Normalize operator */
struct L2NormalizeAttrs : public tvm::AttrsNode<L2NormalizeAttrs> {
  double eps;
  Array<IndexExpr> axis;

  TVM_DECLARE_ATTRS(L2NormalizeAttrs, "relay.attrs.L2NormalizeAttrs") {
    TVM_ATTR_FIELD(eps)
      .describe("A lower bound value for the norm, to avoid division by 0.");
    TVM_ATTR_FIELD(axis)
      .describe("Axis over the normalization applied.");
  }
};

}  // namespace relay
}  // namespace tvm
#endif  // TVM_RELAY_ATTRS_NN_H_
