#include <algorithm>
#include <stack>
#include <string>
#include <vector>

struct Reg_part
{
    std::vector<int> possible;
    Reg_part(size_t k)
    {
        possible.assign(k, -1);
    }
    ~Reg_part()
    {
        possible.clear();
    }
};

bool check(size_t need_size, std::stack<Reg_part>& current_reg)
{
    return current_reg.size() < need_size ? 0 : 1;
}

void put_letter(std::stack<Reg_part>& current_reg, size_t k)
{
    Reg_part part_to_add(k);
    part_to_add.possible[1] = 1;
    current_reg.push(part_to_add);
}

bool put_plus(std::stack<Reg_part>& current_reg, size_t k)
{
    Reg_part first_from_stack(k);
    Reg_part second_from_stack(k);
    Reg_part part_to_add(k);
    if(!check(2, current_reg))
	{
    	return 0;
	}
    first_from_stack = current_reg.top();
    current_reg.pop();
    second_from_stack = current_reg.top();
    current_reg.pop();
    for(size_t i = 0; i < k; ++i)
    {
        if(first_from_stack.possible[i] != -1)
        {
            if(second_from_stack.possible[i] != -1)
            {
                part_to_add.possible[i] = std::min(first_from_stack.possible[i], second_from_stack.possible[i]);
            }
            else
            {
                part_to_add.possible[i] = first_from_stack.possible[i];
            }
        }
        else
        {
            if(second_from_stack.possible[i] != -1)
            {
                part_to_add.possible[i] = second_from_stack.possible[i];
            }
        }
    }
    current_reg.push(part_to_add);
    return 1;
}

bool put_point(std::stack<Reg_part>& current_reg, size_t k)
{
    Reg_part first_from_stack(k);
    Reg_part second_from_stack(k);
    Reg_part part_to_add(k);
    if(!check(2, current_reg))
    {
    	return 0;
    }
    first_from_stack = current_reg.top();
    current_reg.pop();
    second_from_stack = current_reg.top();
    current_reg.pop();
    for(size_t i = 0; i < k; ++i)
    {
        if(first_from_stack.possible[i] != -1)
        {
            for(size_t j = 0; j < k; ++j)
            {
                if(second_from_stack.possible[j] != -1 && (part_to_add.possible[(j + i) % k] == -1 ||
                	part_to_add.possible[(j + i) % k] > first_from_stack.possible[i] + second_from_stack.possible[j]))
                {
                    part_to_add.possible[(j + i) % k] = first_from_stack.possible[i] + second_from_stack.possible[j];
                }
            }
        }
    }
    current_reg.push(part_to_add);
    return 1;
}

bool put_star(std::stack<Reg_part>& current_reg, size_t k)
{
    Reg_part first_from_stack(k);
    Reg_part part_to_add(k);
    if(!check(1, current_reg))
    {
    	return 0;
    }
    first_from_stack = current_reg.top();
    current_reg.pop();
    part_to_add.possible[0] = 0;
    for(size_t i = 0; i < k; ++i)
    {
        if(first_from_stack.possible[i] != -1)
        {
            for(size_t j = 0; j < k; ++j)
            {
                if(part_to_add.possible[(j * first_from_stack.possible[i]) % k] == -1 ||
                	part_to_add.possible[(j * first_from_stack.possible[i]) % k] > first_from_stack.possible[i] * j)
                {
                    part_to_add.possible[(j * first_from_stack.possible[i]) % k] = first_from_stack.possible[i] * j;
                }
            }
        }
    }
    current_reg.push(part_to_add);
    return 1;
}

void put_eps(std::stack<Reg_part>& current_reg, int k)
{
    Reg_part part_to_add(k);
    part_to_add.possible[0] = 0;
    current_reg.push(part_to_add);
}

std::string sol(std::string input_string, size_t k, size_t l)
{
    if(l >= k)
    {
	return "ERROR";
    }
    std::stack<Reg_part> current_reg;
	for(size_t i = 0; i < input_string.size(); ++i)
    {
        if(isalpha(input_string[i]))
        {
            put_letter(current_reg, k);
        }
        else
        {
            switch(input_string[i])
            {
                case '+':
                    if(!put_plus(current_reg, k))
		    {
                    	return "ERROR";
		    }
                    break;
                case '.':
                    if(!put_point(current_reg, k))
		    {
                    	return "ERROR";
		    }
                    break;
                case '*':
                    if(!put_star(current_reg, k))
		    {
                    	return "ERROR";
		    }
                    break;
                case '1':
                    put_eps(current_reg, k);
                    break;
                default:
			return "ERROR";
                    break;
            }
        }
    }
    if(current_reg.size() != 1)
    {
    	return "ERROR";
    }
    Reg_part ans(k);
    ans = current_reg.top();
    if(ans.possible[l] == -1)
    {
        return "INF";
    }
    else
    {
        return std::to_string(ans.possible[l]);
    }
}
