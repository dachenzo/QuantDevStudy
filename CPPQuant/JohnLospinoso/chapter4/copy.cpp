struct Replicant {
    Replicant(Replicant& other) = default;
    Replicant& operator=(const Replicant&) = default;       
};

struct HighLander {
    HighLander(const HighLander& other) = delete;
    HighLander& operator=(const HighLander&) = delete;
};
